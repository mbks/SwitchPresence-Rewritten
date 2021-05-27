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

const char *getAppPlayer(u64 programId)
{
    Result rc;
    AccountUid userID;
    AccountProfile profile;
    AccountUserData userdata;
    AccountProfileBase profilebase;
    memset(&userdata, 0, sizeof(userdata));
    memset(&profilebase, 0, sizeof(profilebase));
    static char nickname[0x21];
     /*if(R_FAILED(rc)) {
        return rc;
    }*/

    rc = accountGetLastOpenedUser(&userID);
    if(R_FAILED(rc)) {
        return "Unknown ID";
    }

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
    return nickname;

}
} // namespace Utils
