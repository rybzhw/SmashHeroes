﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/ActorComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AI/PatrolRoute.h"
#include "BehaviorComponent.generated.h"


/** AI 行为类型 */
UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Idle				UMETA(DisplayName = "Idle"),
	Patrol				UMETA(DisplayName = "Patrol"),
	Seek				UMETA(DisplayName = "Seek"),
	MeleeAttack			UMETA(DisplayName = "MeleeAttack"),
	RangeAttack			UMETA(DisplayName = "RangeAttack"),
	Follow				UMETA(DisplayName = "Follow"),
	Flee				UMETA(DisplayName = "Flee"),
	Investigate			UMETA(DisplayName = "Investigate"),
	Evade				UMETA(DisplayName = "Evade"),
	Guard				UMETA(DisplayName = "Guard"),
	Hit					UMETA(DisplayName = "Hit"),
	Fall				UMETA(DisplayName = "Fall"),
	Dead				UMETA(DisplayName = "Dead")
};

/** 性格类型 */
UENUM(BlueprintType)
enum class EDispositionType : uint8
{
	Aggressive			UMETA(DisplayName = "Aggressive"),	// 侵略型, 倾向通过闪避应对攻击
	Defensive			UMETA(DisplayName = "Defensive"),	// 防守型, 倾向通过防御应对攻击
	Balanced			UMETA(DisplayName = "Balanced")		// 均衡型, 随机应变
};


UENUM()
enum class EIdleType : uint8
{
	Stationary			UMETA(DisplayName = "Stationary"),
	RandomLocation		UMETA(DisplayName = "RandomLocation"),
	RandomWork			UMETA(DisplayName = "RandomWork")
};

UENUM()
enum class EPatrolType : uint8
{
	Disabled			UMETA(DisplayName = "Disabled"),
	Single				UMETA(DisplayName = "Single"),
	Looping				UMETA(DisplayName = "Looping"),
	BackAndForth		UMETA(DisplayName = "BackAndForth")
};

/** Idle开始时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FIdleBeginDelegate);
/** Patrol开始时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPatrolBeginDelegate);
/** Seek开始时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSeekBeginDelegate);
/** Melee Attack开始时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMeleeAttackBeginDelegate);
/** Range Attack开始时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRangeAttackBeginDelegate);
/** Follow开始时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFollowBeginDelegate);
/** Flee开始时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFleeBeginDelegate);
/** Investigate开始时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInvestigateBeginDelegate);
/** Evade开始时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEvadeBeginDelegate);
/** Guard开始时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGuardBeginDelegate);
/** Hit开始时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHitBeginDelegate);
/** Fall开始时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFallBeginDelegate);
/** Dead开始时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeadBeginDelegate);

/** Idle结束时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FIdleEndDelegate);
/** Patrol结束时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPatrolEndDelegate);
/** Seek结束时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSeekEndDelegate);
/** Melee Attack结束时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMeleeAttackEndDelegate);
/** Range Attack结束时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRangeAttackEndDelegate);
/** Follow结束时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFollowEndDelegate);
/** Flee结束时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFleeEndDelegate);
/** Investigate结束时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInvestigateEndDelegate);
/** Evade结束时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEvadeEndDelegate);
/** Guard结束时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGuardEndDelegate);
/** Hit结束时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHitEndDelegate);
/** Fall结束时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFallEndDelegate);
/** Dead结束时调用 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeadEndDelegate);

UCLASS(ClassGroup=AIBehavior, hidecategories=(Object,LOD,Lighting,Transform,Sockets,TextureStreaming), editinlinenew, meta=(BlueprintSpawnableComponent))
class SMASHHEROES_API UBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** 是否由AI控制 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	bool bIsAI = false;

	/** 性格类型 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	EDispositionType Disposition = EDispositionType::Balanced;

	/** 当前AI使用的行为树 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	UBehaviorTree* BehaviorTree;

	/** 初始行为 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	EBehaviorType InitBehavior = EBehaviorType::Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	FName BBKey_CurrentBehaviorType = FName(TEXT("CurrentBehaviorType"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	FName BBKey_TargetBehaviorType = FName(TEXT("TargetBehaviorType"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	FName BBKey_TargetActor = FName(TEXT("TargetActor"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	FName BBKey_StartLocation = FName(TEXT("StartLocation"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	FName BBKey_TargetLocation = FName(TEXT("TargetLocation"));

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General Settings")
	FName BBKey_IdleType = FName(TEXT("IdleType"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	FName BBKey_MaxRandLocationDistance = FName(TEXT("MaxRandLocationDistance"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	FName BBKey_RandLocationDelay = FName(TEXT("RandLocationDelay"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	FName BBKey_FleeDistance = FName(TEXT("FleeDistance"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	FName BBKey_MeleeAttackDistance = FName(TEXT("MeleeAttackDistance"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	FName BBKey_RangeAttackDistance = FName(TEXT("RangeAttackDistance"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	FName BBKey_MinFightMoveSpeed = FName(TEXT("MinFightMoveSpeed"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	FName BBKey_MaxFightMoveSpeed = FName(TEXT("MaxFightMoveSpeed"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	FName BBKey_FightMoveProb = FName(TEXT("FightMoveProb"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	FName BBKey_FollowDistance = FName(TEXT("FollowDistance"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	FName BBKey_SeekAcceptanceRadius = FName(TEXT("SeekAcceptanceRadius"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	FName BBKey_FollowAcceptanceRadius = FName(TEXT("FollowAcceptanceRadius"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	FName BBKey_InvestigateDistance = FName(TEXT("InvestigateDistance"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	FName BBKey_InvestigateInterval = FName(TEXT("InvestigateInterval"));

	/** 闲置行为类型 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle Settings")
	EIdleType IdleType = EIdleType::Stationary;

	/** 最大随机走动距离 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle Settings")
	float MaxRandLocationDistance = 300.0f;

	/** 随机走动间隔 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle Settings")
	float RandLocationDelay = 10.0f;

	/** 巡逻路径名称 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Patrol Settings")
	FString PatrolRouteName;

	/** 巡逻路径 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Patrol Settings")
	APatrolRoute* PatrolRoute;

	/** 最小巡逻移动速度 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol Settings")
	float MinPatrolMoveSpeed = 300.0f;

	/** 最大巡逻移动速度 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol Settings")
	float MaxPatrolMoveSpeed = 340.0f;

	/** 巡逻类型 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Patrol Settings")
	EPatrolType PatrolType = EPatrolType::BackAndForth;

	/** 巡逻点索引 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol Settings")
	int32 PatrolSplineIndex = -1;

	/** 巡逻方向, true:正向, false:反向, 目前仅用于BackAndForth巡逻类型 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Patrol Settings")
	bool PatrolDirection = true;

	/** 巡逻行为结束后进入的下一行为类型 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol Settings")
	EBehaviorType PatrolTransition = EBehaviorType::Idle;

	/** 侦查距离 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Investigate Settings")
	float InvestigateDistance = 3000.0f;

	/** 侦查间隔 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Investigate Settings")
	float InvestigateInterval = 0.2f;

	/** 侦查行为结束后进入的下一行为类型 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Investigate Settings")
	EBehaviorType InvestigateTransition = EBehaviorType::Idle;

	/** 追踪距离 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Follow Settings")
	float FollowDistance = 2000.0f;

	/** 追踪行为的可接受半径 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Follow Settings")
	float FollowAcceptanceRadius = 100.0f;

	/** 最小追踪移动速度 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Follow Settings")
	float MinFollowMoveSpeed = 400.0f;

	/** 最大追踪移动速度 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Follow Settings")
	float MaxFollowMoveSpeed = 420.0f;

	/** 是否会逃离 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flee Settings")
	bool bCanFlee = true;

	/** 触发逃离的血量百分比 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flee Settings")
	float FleeHealthThreshold = 0.2f;

	/** 逃离距离 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flee Settings")
	float FleeDistance = 1600.0f;

	/** 逃离行为结束后进入的下一行为类型 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flee Settings")
	EBehaviorType FleeTransition = EBehaviorType::Idle;

	/** 最小逃跑移动速度 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flee Settings")
	float MinFleeMoveSpeed = 560.0f;

	/** 最大逃跑移动速度 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flee Settings")
	float MaxFleeMoveSpeed = 600.0f;

	/** 寻找目标的Tag数组 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Seek Settings")
	TArray<FName> SeekTargetTags;

	/** 寻找行为的可接受半径 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Seek Settings")
	float SeekAcceptanceRadius;

	/** 寻找行为结束后进入的下一行为类型 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Seek Settings")
	EBehaviorType SeekTransition = EBehaviorType::Idle;		

	/** 最小搜寻移动速度 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Seek Settings")
	float MinSeekMoveSpeed = 560.0f;

	/** 最大搜寻移动速度 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Seek Settings")
	float MaxSeekMoveSpeed = 600.0f;

	/** 近战攻击距离 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Settings")
	float MeleeAttackDistance = 200.0f;

	/** 是否支持远程攻击 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Settings")
	bool CanRangeAttack = false;

	/** 范围攻击距离 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Settings")
	float RangeAttackDistance = 1600.0f;

	/** 战斗胶着状态下最小移动速度 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Settings")
	float MinFightMoveSpeed = 150.0f;

	/** 战斗胶着状态下最大移动速度 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Settings")
	float MaxFightMoveSpeed = 200.0f;

	/** 战斗胶着状态触发概率 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Settings")
	float FightMoveProb = 1.0f;

	/** 攻击是否需要考虑在视野内 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Settings")
	bool IsRequireLineOfSight = true;

	/** 可攻击目标的Tag数组 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Settings")
	TArray<FName> AttackTargetTags;

	/** 近战攻击行为结束后进入的下一行为类型 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Settings")
	EBehaviorType MeleeAttackTransition = EBehaviorType::Idle;

	/** 远程攻击行为结束后进入的下一行为类型 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Settings")
	EBehaviorType RangeAttackTransition = EBehaviorType::Idle;

	/** 初始仇恨值 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Settings")
	float InitHateValue = 100.0f;
	
	/** 仇恨列表(仅用于AI), 仇恨值 = 初始仇恨值 + 受到来自仇恨目标的伤害值 + （“嘲讽”等特殊技能带来的仇恨值增量） */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack Settings")
	TMap<AActor*, float> HateTargets;

	/** 防守行为结束后进入的下一行为类型 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Evade Settings")
	EBehaviorType EvadeTransition = EBehaviorType::Idle;

	/** 防守行为结束后进入的下一行为类型 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guard Settings")
	EBehaviorType GuardTransition = EBehaviorType::Idle;

	/** 受击行为结束后进入的下一行为类型 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Settings")
	EBehaviorType HitTransition = EBehaviorType::Idle;

	/** 死亡行为结束后进入的下一行为类型 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dead Settings")
	EBehaviorType DeadTransition = EBehaviorType::Idle;

	/** 行为开始相关委托 */
	UPROPERTY(BlueprintAssignable)
	FIdleBeginDelegate OnIdleBegin;

	UPROPERTY(BlueprintAssignable)
	FPatrolBeginDelegate OnPatrolBegin;

	UPROPERTY(BlueprintAssignable)
	FSeekBeginDelegate OnSeekBegin;

	UPROPERTY(BlueprintAssignable)
	FMeleeAttackBeginDelegate OnMeleeAttackBegin;

	UPROPERTY(BlueprintAssignable)
	FRangeAttackBeginDelegate OnRangeAttackBegin;

	UPROPERTY(BlueprintAssignable)
	FFollowBeginDelegate OnFollowBegin;

	UPROPERTY(BlueprintAssignable)
	FFleeBeginDelegate OnFleeBegin;

	UPROPERTY(BlueprintAssignable)
	FInvestigateBeginDelegate OnInvestigateBegin;

	UPROPERTY(BlueprintAssignable)
	FEvadeBeginDelegate OnEvadeBegin;

	UPROPERTY(BlueprintAssignable)
	FGuardBeginDelegate OnGuardBegin;

	UPROPERTY(BlueprintAssignable)
	FHitBeginDelegate OnHitBegin;

	UPROPERTY(BlueprintAssignable)
	FFallBeginDelegate OnFallBegin;

	UPROPERTY(BlueprintAssignable)
	FDeadBeginDelegate OnDeadBegin;

	/** 行为结束相关委托 */
	UPROPERTY(BlueprintAssignable)
	FIdleEndDelegate OnIdleEnd;

	UPROPERTY(BlueprintAssignable)
	FPatrolEndDelegate OnPatrolEnd;

	UPROPERTY(BlueprintAssignable)
	FSeekEndDelegate OnSeekEnd;

	UPROPERTY(BlueprintAssignable)
	FMeleeAttackEndDelegate OnMeleeAttackEnd;

	UPROPERTY(BlueprintAssignable)
	FRangeAttackEndDelegate OnRangeAttackEnd;

	UPROPERTY(BlueprintAssignable)
	FFollowEndDelegate OnFollowEnd;

	UPROPERTY(BlueprintAssignable)
	FFleeEndDelegate OnFleeEnd;

	UPROPERTY(BlueprintAssignable)
	FInvestigateEndDelegate OnInvestigateEnd;

	UPROPERTY(BlueprintAssignable)
	FEvadeEndDelegate OnEvadeEnd;

	UPROPERTY(BlueprintAssignable)
	FGuardEndDelegate OnGuardEnd;

	UPROPERTY(BlueprintAssignable)
	FHitEndDelegate OnHitEnd;

	UPROPERTY(BlueprintAssignable)
	FFallEndDelegate OnFallEnd;

	UPROPERTY(BlueprintAssignable)
	FDeadEndDelegate OnDeadEnd;

private:
	UPROPERTY(VisibleAnywhere, Category = "General Settings")
	AActor* OwnerActor;

	UPROPERTY(VisibleAnywhere, Category = "General Settings")
	AAIController* OwnerAIController;

	/** 目标行为, AI专用 */
	UPROPERTY(VisibleAnywhere, Category = "General Settings")
	EBehaviorType TargetBehavior = EBehaviorType::Idle;

	/** 上一次的行为 */
	UPROPERTY(VisibleAnywhere, Category = "General Settings")
	EBehaviorType LastBehavior = EBehaviorType::Idle;

	/** 当前行为 */
	UPROPERTY(VisibleAnywhere, Category = "General Settings")
	EBehaviorType CurrentBehavior = EBehaviorType::Idle;

	/** 当前行为是否由其他行为结束过渡所至 */
	UPROPERTY(VisibleAnywhere, Category = "General Settings")
	bool bIsTransition = false;

	/** 寻找目标(不同于AttackTarget, 需要通过外部指定) */
	UPROPERTY(VisibleAnywhere, Category = "Seek Settings")
	AActor* SeekTarget;

	/** 巡逻是否结束标记(仅在PatrolType=Single时有效) */
	UPROPERTY(VisibleAnywhere, Category = "Patrol Settings")
	bool bIsPatrolEnded = false;

	UPROPERTY(VisibleAnywhere, Category = "Attack Settings")
	AActor* AttackTarget;

public:	
	// Sets default values for this component's properties
	UBehaviorComponent();

	/** 初始化行为组件 */
	void Initialize();

	/** 根据Key初始化Blackboard中的值 */
	void InitBlackboard();

	/** 行为切换相关事件, 在GameplayAbility或BTTask中调用 */
	UFUNCTION(BlueprintCallable)
	virtual void BeginMeleeAttack();

	UFUNCTION(BlueprintCallable)
	virtual void EndMeleeAttack();

	UFUNCTION(BlueprintCallable)
	virtual void BeginRangeAttack();

	UFUNCTION(BlueprintCallable)
	virtual void EndRangeAttack();

	UFUNCTION(BlueprintCallable)
	virtual void BeginEvade();

	UFUNCTION(BlueprintCallable)
	virtual void EndEvade();

	UFUNCTION(BlueprintCallable)
	virtual void BeginGuard();

	UFUNCTION(BlueprintCallable)
	virtual void EndGuard();

	UFUNCTION(BlueprintCallable)
	virtual void BeginHit();

	UFUNCTION(BlueprintCallable)
	virtual void EndHit();

	UFUNCTION(BlueprintCallable)
	virtual void BeginDead();

	UFUNCTION(BlueprintCallable)
	virtual void EndDead();

	/** 设置寻找目标(外部调用) */
	void SetSeekTarget(AActor* NewSeekTarget);

	/** 清除寻找目标(在死亡时回调) */
	UFUNCTION()
	void ResetSeekTarget();

	/** 确定寻找目标 */
	AActor* FindSeekTarget(float &DistToTarget);

	/** 获取寻找目标(外部调用) */
	AActor* GetSeekTarget();

	/** 添加新的仇恨目标, 并设置初始仇恨值(发现目标时调用) */
	void AddHateTarget(AActor* NewTarget);

	/** 更新仇恨目标列表 */
	void UpdateHateTargets();

	/** 更新已有目标仇恨值(受击时调用)或添加新的仇恨目标 */
	void UpdateTargetHateValue(AActor *NewTarget, float HateValue);

	/** 添加新的仇恨目标或更新已有目标仇恨值 */
	void RemoveHateTarget(AActor *Target);

	/** 获取仇恨值最高的最近目标 */
	AActor* GetHatestNearTarget(float &DistToTarget);

	/** 清空所有仇恨目标 */
	UFUNCTION()
	void ResetHateTargets();

	/** 根据仇恨列表确定攻击目标 */
	AActor* FindAttackTarget(float &DistToTarget);

	/** 清除攻击目标(在死亡或攻击结束时回调) */
	UFUNCTION()
	void ResetAttackTarget();

	/** 获取当前攻击目标对象 */
	UFUNCTION(BlueprintCallable)
	AActor* GetAttackTarget();

	/** 根据指定Tag找到最近的目标 */
	UFUNCTION(BlueprintCallable)
	AActor* FindNearestTargetWithTag(TArray<FName> TargerTags, float &DistToTarget);

	/** 更新巡逻路径 */
	UFUNCTION(BlueprintCallable)
	void UpdatePatrolRoute();

	/** 寻找下一个巡逻点 */
	UFUNCTION(BlueprintCallable)
	void FindNextPatrolLocation();

	/** 获取当前行为类型 */
	UFUNCTION(BlueprintPure)
	EBehaviorType GetBehavior() const;

	/** 设置黑板行为信息 */
	UFUNCTION(BlueprintCallable)
	bool ChangeBehavior(EBehaviorType NewBehavior);

	/** 更新行为 */
	UFUNCTION(BlueprintCallable)
	void UpdateBehavior();

	/** 行为过渡 */
	UFUNCTION(BlueprintCallable)
	void TransitionBehavior();

	/** 设置目标行为 */
	UFUNCTION(BlueprintCallable)
	void SetTargetBehavior(EBehaviorType NewBehavior);

	/** 获取目标行为 */
	UFUNCTION(BlueprintPure)
	EBehaviorType GetTargetBehavior();

	/** 根据性格类型采取攻击应对措施(闪避、防御) */
	UFUNCTION(BlueprintCallable)
	EBehaviorType DealWithAttack();

	/** 更新当前移动速度 */
	UFUNCTION(BlueprintCallable)
	void UpdateMoveSpeed();
};
