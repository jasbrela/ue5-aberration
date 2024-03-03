#pragma once

#include "CoreMinimal.h"

#define LOG(Format, ...)  if (GEngine) { \
FString Message = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("%s() : %s"), FUNC_NAME, *Message)); \
UE_LOG(LogTemp, Log, TEXT("[%s()] %s"), FUNC_NAME, *Message);\
}

#define LOG_WARNING(Format, ...) if (GEngine) { \
FString Message = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("%s() : %s"), FUNC_NAME, *Message)); \
UE_LOG(LogTemp, Warning, TEXT("[%s()] %s"), FUNC_NAME, *Message); \
}

#define LOG_SUCCESS(Format, ...) if (GEngine) { \
FString Message = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%s() : %s"), FUNC_NAME, *Message)); \
UE_LOG(LogTemp, Log, TEXT("[%s()] %s"), FUNC_NAME, *Message); \
}

#define LOG_ERROR(Format, ...) if (GEngine) { \
FString Message = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s() : %s"), FUNC_NAME, *Message)); \
UE_LOG(LogTemp, Error, TEXT("[%s()] %s"), FUNC_NAME, *Message); \
}


#if _MSC_VER
#define FUNC_NAME    TEXT(__FUNCTION__)
#else // FIXME - GCC?
#define FUNC_NAME    TEXT(__func__)
#endif
