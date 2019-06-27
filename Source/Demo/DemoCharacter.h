// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DemoCharacter.generated.h"

class UTimelineComponent;

UCLASS(config=Game)
class ADemoCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ADemoCharacter();
	

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float HealthPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		bool redFlash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		bool gameStart;

	UTimelineComponent* MyTimeline;
	struct FTimerHandle MemberTimerHandle;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
		bool IsTrap;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION()
		virtual void BeginPlay();

	UFUNCTION()
		virtual void Tick(float DeltaTime) override;
	

	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealth();

	UFUNCTION(BlueprintPure, Category = "Health")
		FText GetHealthIntText();

	UFUNCTION()
		void DamageTimer();

	UFUNCTION()
		void SetDamageState();

	UFUNCTION(BlueprintPure, Category = "Health")
		bool PlayFlash();

	UFUNCTION(BlueprintCallable, Category = "Health")
		void RecievePointDamage(float Damage,
			const class UDamageType * DamageType,
			FVector HitLocation,
			FVector HitNormal,
			class UPrimitiveComponent * HitComponent,
			FName BoneName,
			FVector ShotFromDirection,
			class AController * InstigatedBy,
			AActor * DamageCauser,
			const FHitResult & HitInfo);

	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);

	UFUNCTION(BlueprintCallable, Category = "Health")
		void UpdateHealth(float HealthChange);

};

