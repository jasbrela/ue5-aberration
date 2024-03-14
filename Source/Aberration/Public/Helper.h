#pragma once

template<typename T>

static TArray<T> ShuffleArray(TArray<T> Array, FRandomStream Stream)
{
	const int32 NumShuffles = Array.Num() - 1;
	for(int32 i = 0 ; i < NumShuffles ; ++i)
	{
		const int32 Index = Stream.RandRange(i, NumShuffles);
		Array.Swap(i, Index);
	}
	return Array;
}

static FText Convert(float value)
{
	return FText::FromString(FString::Printf(TEXT("%.2f"), value));
}