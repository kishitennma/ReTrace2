#include "WarpPortal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "NiagaraFunctionLibrary.h"
#include "TimerManager.h"

AWarpPortal::AWarpPortal()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(Root);
    TriggerBox->SetRelativeLocation(FVector::ZeroVector);
    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    PortalEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PortalEffect"));
    PortalEffect->SetupAttachment(Root);
    PortalEffect->SetRelativeLocation(FVector::ZeroVector);
    PortalEffect->SetUsingAbsoluteScale(true); // BP ã‚ÌƒXƒP[ƒ‹‚ª•ö‚ê‚È‚¢‚æ‚¤‚É
    PortalEffect->bAutoActivate = true;
    PortalEffect->bIsEditorOnly = false;
}

void AWarpPortal::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (PortalEffectAsset)
    {
        PortalEffect->SetAsset(PortalEffectAsset);
        PortalEffect->Activate(true);
        PortalEffect->SetWorldLocation(GetActorLocation());
    }

    TriggerBox->SetWorldLocation(GetActorLocation());
}

void AWarpPortal::BeginPlay()
{
    Super::BeginPlay();

    if (PortalEffectAsset)
    {
        PortalEffect->SetAsset(PortalEffectAsset);
        PortalEffect->Activate(true);
        PortalEffect->SetWorldLocation(GetActorLocation());
    }

    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AWarpPortal::OnOverlapBegin);
}

void AWarpPortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!bCanTeleport || !TargetPortal) return;

    ACharacter* Player = Cast<ACharacter>(OtherActor);
    if (!Player) return;

    bCanTeleport = false;
    TargetPortal->bCanTeleport = false;

    FVector NewLocation = TargetPortal->GetActorLocation();
    FRotator NewRotation = TargetPortal->GetActorRotation();

    Player->SetActorLocation(NewLocation);
    Player->SetActorRotation(NewRotation);

    FTimerHandle TimerHandle;
    GetWorldTimerManager().SetTimer(TimerHandle, [this]() { bCanTeleport = true; }, 1.0f, false);
    GetWorldTimerManager().SetTimer(TimerHandle, [Target = TargetPortal]() { Target->bCanTeleport = true; }, 1.0f, false);
}
