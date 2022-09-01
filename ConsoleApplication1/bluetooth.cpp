#include "base.h"

struct device {
    U8 name[BLUETOOTH_MAX_NAME_SIZE];
    MAC addr;
    U16 cls;
    bool connected;
    bool remembered;
    bool authentificate;
    device(BLUETOOTH_DEVICE_INFO info)
    {
        U8 ctr;
        for (ctr = 0; ctr < BLUETOOTH_MAX_NAME_SIZE; ctr++) name[ctr] = 0;
        for (ctr = 0; ctr < ETH_ALEN; ctr++) addr[ctr] = 0;
        cls = info.ulClassofDevice;
        connected = info.fConnected;
        remembered = info.fRemembered;
        authentificate = info.fAuthenticated;
        memcpy(name, info.szName, BLUETOOTH_MAX_NAME_SIZE);
        memcpy(addr, info.Address.rgBytes, ETH_ALEN);
    }
};

void print_device(device dv) {
    char mac[MAC_STR_LEN];
    for (U8 ctr = 0; ctr < MAC_STR_LEN; ctr++) mac[ctr] = 0;
    mac2str(mac, dv.addr);
    print("Device: %S\n%sMAC: %s\n%sClass: %lu\n%sConnected: %d\n%sRemembered: %d\n%sAuthentificated: %d\n", dv.name, PRINT_TIME_TAB, mac, PRINT_TIME_TAB, dv.cls, PRINT_TIME_TAB, dv.connected, PRINT_TIME_TAB, dv.remembered, PRINT_TIME_TAB, dv.authentificate);
}

int find_dongle(HANDLE &hradio) {
    BLUETOOTH_RADIO_INFO radioInfo;
    BLUETOOTH_FIND_RADIO_PARAMS btfrp = { sizeof(BLUETOOTH_FIND_RADIO_PARAMS) };
    HBLUETOOTH_RADIO_FIND hFind = BluetoothFindFirstRadio(&btfrp, &hradio);
    hFind = BluetoothFindFirstRadio(&btfrp, &hradio);
    if (!hFind) {
        print("Hfind");
        return -1;
    }
    radioInfo.dwSize = sizeof(radioInfo);
    if (BluetoothGetRadioInfo(hradio, &radioInfo) != ERROR_SUCCESS) return -1;
    print("Finded dongle with name: %S", radioInfo.szName);
    return 0;
}

int mains(int argc, char** argv) {
    HANDLE hRadio;
    if (find_dongle(hRadio) < 0) {
        print("No bluetooth adapter found!");
    }
    device* devices;

    return 0;
} 
int main(int argc, char** argv)

{

    HANDLE hRadio, hDeviceFind;

    BLUETOOTH_DEVICE_INFO_STRUCT deviceInfo;

    BLUETOOTH_DEVICE_SEARCH_PARAMS deviceSearchParams;

    BLUETOOTH_RADIO_INFO radioInfo;

    GUID guidServices[10];

    DWORD numServices, result;

    int i = 1;



    BLUETOOTH_FIND_RADIO_PARAMS btfrp = { sizeof(BLUETOOTH_FIND_RADIO_PARAMS) };

    HBLUETOOTH_RADIO_FIND hFind = BluetoothFindFirstRadio(&btfrp, &hRadio);



    if (hFind != NULL)

    {

        printf("BluetoothFindFirstRadio() is working!\n");

        do

        {

            // Do something with the radio handle...

            radioInfo.dwSize = sizeof(radioInfo);



            if (BluetoothGetRadioInfo(hRadio, &radioInfo) == ERROR_SUCCESS)

            {

                printf("BluetoothGetRadioInfo() is OK!\n");

                printf(" Radio found: %S\n", radioInfo.szName);

            }

            else

                printf("BluetoothGetRadioInfo() failed with error code %d\n", GetLastError());



            deviceInfo.dwSize = sizeof(deviceInfo);

            memset(&deviceSearchParams, 0, sizeof(deviceSearchParams));

            deviceSearchParams.dwSize = sizeof(deviceSearchParams);



            deviceSearchParams.fReturnAuthenticated = TRUE;

            deviceSearchParams.fReturnRemembered = TRUE;

            deviceSearchParams.fReturnUnknown = TRUE;

            deviceSearchParams.fReturnConnected = TRUE;

            deviceSearchParams.hRadio = hRadio;


            hDeviceFind = BluetoothFindFirstDevice(&deviceSearchParams, &deviceInfo);

            if (hDeviceFind != NULL)

            {

                printf("BluetoothFindFirstDevice() is OK!\n");

                do

                {
                    /*
                    printf(" Device found - Name: %S\n", deviceInfo.szName);

                    printf(" Device found - Address: %X\n", deviceInfo.Address);

                    printf(" Device found - Device Class: %ul\n", deviceInfo.ulClassofDevice);
                    */
                    device devic(deviceInfo);
                    print_device(devic);
                    numServices = sizeof(guidServices);









                    // guidServices should contains a complete list of enabled service GUIDs.

                    result = BluetoothEnumerateInstalledServices(hRadio, &deviceInfo, &numServices, guidServices);



                    if (result == ERROR_SUCCESS)

                    {

                        printf("BluetoothEnumerateInstalledServices() should be fine!\n");

                        printf(" ...GUID services\n");

                    }

                    else

                        printf("BluetoothEnumerateInstalledServices() failed with error code %d\n", result);



                }

                while (BluetoothFindNextDevice(hDeviceFind, &deviceInfo));



                BluetoothFindDeviceClose(hDeviceFind);

            }



            // Need to re-allocate, else BluetoothGetDeviceInfo() will fail

            memset(&deviceInfo, 0, sizeof(deviceInfo));

            deviceInfo.dwSize = sizeof(deviceInfo);



            if (BluetoothGetDeviceInfo(hRadio, &deviceInfo))

            {

                printf("BluetoothGetDeviceInfo() is OK!\n");

                printf(" ...More operations...\n");

                // BluetoothUpdateDeviceRecord() - change name, BluetoothRemoveDevice() etc.

            }

            else

                printf("BluetoothGetDeviceInfo() failed with error code %d\n", GetLastError());



            CloseHandle(hRadio);

        } while (BluetoothFindNextRadio(hFind, &hRadio));

        BluetoothFindRadioClose(hFind);

    }

    return 0;

}