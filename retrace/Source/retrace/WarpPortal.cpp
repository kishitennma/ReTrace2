#include "WarpPortal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

AWarpPortal::AWarpPortal()
{
    PrimaryActorTick.bCanEverTick = false;

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    PortalEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PortalEffect"));
    PortalEffect->SetupAttachment(RootComponent);
    PortalEffect->bAutoActivate = false; 
}

void AWarpPortal::BeginPlay()
{
    Super::BeginPlay();

    if (PortalEffectAsset)
    {
        PortalEffect->SetAsset(PortalEffectAsset);
        PortalEffect->Activate(true);   // ループで表示し続ける！
    }

    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AWarpPortal::OnOverlapBegin);
}

void AWarpPortal::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    if (!bCanTeleport) return;
    if (!TargetPortal) return;

    ACharacter* Player = Cast<ACharacter>(OtherActor);
    if (!Player) return;

    // 再発動防止（無限ループ対策）
    bCanTeleport = false;
    TargetPortal->bCanTeleport = false;

    // 移動先座標
    FVector NewLocation = TargetPortal->GetActorLocation();
    FRotator NewRotation = TargetPortal->GetActorRotation();

    Player->SetActorLocation(NewLocation);
    Player->SetActorRotation(NewRotation);

    // 一定時間後に再度テレポート可能に
    FTimerHandle TimerHandle;
    GetWorldTimerManager().SetTimer(TimerHandle, [this]() {
        bCanTeleport = true;
        }, 1.0f, false);

    GetWorldTimerManager().SetTimer(TimerHandle, [Target = TargetPortal]() {
        Target->bCanTeleport = true;
        }, 1.0f, false);

   

}
