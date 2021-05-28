#include "Utils.h"
#include <cstring>

namespace Utils
{
const char *getAppName(u64 programId)
{
    static NsApplicationControlData appControlData;
    size_t appControlDataSize;
    NacpLanguageEntry *languageEntry;

    memset(&appControlData, 0, sizeof(NsApplicationControlData));

    if (R_SUCCEEDED(nsGetApplicationControlData(NsApplicationControlSource_Storage, programId, &appControlData, sizeof(NsApplicationControlData), &appControlDataSize)))
    {
        if (R_SUCCEEDED(nacpGetLanguageEntry(&appControlData.nacp, &languageEntry)))
        {
            if (languageEntry != nullptr)
                return languageEntry->name;
        }
    }
    return "A Game";
}

static char nickname[33];

const char *getAppPlayer(AccountUid userID)
{
    Result rc;
    AccountProfile profile;
    AccountUserData userdata;
    AccountProfileBase profilebase;
    memset(&userdata, 0, sizeof(userdata));
    memset(&profilebase, 0, sizeof(profilebase));

    rc = accountGetProfile(&profile, userID);
    if (R_FAILED(rc)) {
                return "Unknown profile";
    }

    rc = accountProfileGet(&profile, &userdata, &profilebase);
    if (R_FAILED(rc)) {
                return "Invalid profile";
    }
    memset(nickname,  0, sizeof(nickname));
    strncpy(nickname, profilebase.nickname, sizeof(nickname)-1);
    accountProfileClose(&profile);

    return nickname;

}
} // namespace Utils
