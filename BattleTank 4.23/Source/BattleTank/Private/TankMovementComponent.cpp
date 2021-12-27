// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
		LeftTrack->SetThrottleForce(Throw);
		RightTrack->SetThrottleForce(Throw);
}
void UTankMovementComponent::Initialise(UTankTrack* RightTrackToSet, UTankTrack* LeftTrackToSet)
{
	if (RightTrackToSet && LeftTrackToSet) {
		RightTrack = RightTrackToSet;
		LeftTrack = LeftTrackToSet;
	}
}