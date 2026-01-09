#include "SpeedPadActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

ASpeedPadActor::ASpeedPadActor()
{
    PrimaryActorTick.bCanEverTick = true;
    SetActorTickEnabled(false);

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;
    Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Mesh->SetCollisionResponseToAllChannels(ECR_Overlap);

    Mesh->OnComponentBeginOverlap.AddDynamic(this, &ASpeedPadActor::OnOverlapBegin);
    Mesh->OnComponentEndOverlap.AddDynamic(this, &ASpeedPadActor::OnOverlapEnd);

    DirectionRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DirectionRoot"));
    DirectionRoot->SetupAttachment(Mesh);

    DirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("DirectionArrow"));
    DirectionArrow->SetupAttachment(DirectionRoot);
    DirectionArrow->ArrowSize = 2.f;
    DirectionArrow->bIsEditorOnly = true;
}

void ASpeedPadActor::BeginPlay()
{
    Super::BeginPlay();
}

void ASpeedPadActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!OverlappingPlayer) return;

    FVector FloorDir = DirectionRoot->GetForwardVector().GetSafeNormal();
    FVector PlayerInput = OverlappingPlayer->GetLastMovementInputVector();

    FVector CurrentVel = OverlappingPlayer->GetVelocity();

    // ベース速度は常に FloorDir 方向
    FVector TargetVel = FloorDir * BaseSpeed;

    // 正方向入力があれば加速
    if (!PlayerInput.IsNearlyZero())
    {
        float Dot = FVector::DotProduct(PlayerInput.GetSafeNormal(), FloorDir);
        if (Dot > 0.f)
        {
            TargetVel += FloorDir * AcceleratePower * Dot;
        }
    }

    // 逆走不可なので Dot <=0 は無視

    // Velocity に反映（Z は保持）
    FVector NewVel = FVector(TargetVel.X, TargetVel.Y, CurrentVel.Z);
    OverlappingPlayer->GetCharacterMovement()->Velocity = NewVel;
}


void ASpeedPadActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    ACharacter* Player = Cast<ACharacter>(OtherActor);
    if (!Player) return;

    OverlappingPlayer = Player;
    SetActorTickEnabled(true);
}

void ASpeedPadActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    ACharacter* Player = Cast<ACharacter>(OtherActor);
    if (!Player) return;

    if (OverlappingPlayer == Player)
    {
        OverlappingPlayer = nullptr;
        SetActorTickEnabled(false);
    }
}
