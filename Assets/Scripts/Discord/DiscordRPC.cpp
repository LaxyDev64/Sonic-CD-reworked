#include "discord_game_sdk.h"
#include <ctime>

static discord::Core* core{};
static int64_t startTime;

void InitDiscordRPC()
{
    discord::Core::Create(
        123456789012345678, // TU APPLICATION ID
        DiscordCreateFlags_Default,
        &core
    );

    startTime = std::time(nullptr);
}
void UpdateDiscordRPC(const char* zone, const char* act, const char* timePeriod)
{
    if (!core) return;

    discord::Activity activity{};
    activity.SetState(timePeriod);            // Past / Present / Future
    activity.SetDetails(zone);                 // Zona actual
    activity.GetAssets().SetLargeImage("icon");
    activity.GetAssets().SetLargeText("Sonic CD Reworked");
    activity.GetTimestamps().SetStart(startTime);

    core->ActivityManager().UpdateActivity(activity, nullptr);
}
void ShutdownDiscordRPC()
{
    if (core)
    {
        delete core;
        core = nullptr;
    }
}
void RunDiscordCallbacks()
{
    if (core)
    {
        core->RunCallbacks();
    }
}