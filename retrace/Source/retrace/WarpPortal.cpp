#include "WarpPortal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "NiagaraFunctionLibrary.h"
#include "MyCharacter.h"
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
    PortalEffect->SetUsingAbsoluteScale(true); // BP 上のスケールが崩れないように
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

    // ★ MyCharacter 以外は無視
    AMyCharacter* Player = Cast<AMyCharacter>(OtherActor);
    if (!Player) return;

    bCanTeleport = false;
    TargetPortal->bCanTeleport = false;

    FVector NewLocation = TargetPortal->GetActorLocation();
    FRotator NewRotation = TargetPortal->GetActorRotation();

    Player->SetActorLocation(NewLocation);
    Player->SetActorRotation(NewRotation);

    // テレポート拘束解除
    FTimerHandle TimerHandle1;
    GetWorldTimerManager().SetTimer(TimerHandle1, [this]()
        {
            bCanTeleport = true;
        }, 1.0f, false);

    FTimerHandle TimerHandle2;
    GetWorldTimerManager().SetTimer(TimerHandle2, [Target = TargetPortal]()
        {
            Target->bCanTeleport = true;
        }, 1.0f, false);
}