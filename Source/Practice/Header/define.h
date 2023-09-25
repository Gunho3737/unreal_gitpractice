#pragma once

DECLARE_LOG_CATEGORY_EXTERN(Player, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(Monster, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(AI, Log, All);



#define LOG(Category, Verbosity, String)    UE_LOG(Category, Verbosity, \
                                            TEXT("%s"), *FString::Printf(TEXT("%s : {%d} : %s"), \
                                            *FString(__FUNCTION__), __LINE__, String));