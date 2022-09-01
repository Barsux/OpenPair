#pragma once
#ifndef BASEH
#define BASEH

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include <stdarg.h>
#include <inttypes.h>
#include <time.h>
#include <new>
#ifdef __linux__
#include "sys/socket.h"
#include <sys/select.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <linux/if_packet.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <netinet/ether.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/fs.h>
#include "inttypes.h"
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <time.h>
#else
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Bthprops.lib")
#include <winsock2.h>
#include <windows.h>
#include <ws2bth.h>
#include <BluetoothAPIs.h>

#define UTC_Amend 11644473600000000000
#define MS_NS 1000000
#define S_NS MS_NS * 1000
#define M_NS S_NS * 60
#define H_NS M_NS * 60
#define ETH_ALEN 6
#define MAC_STR_LEN 19
#define PRINT_TIME_TAB "                           "


typedef uint64_t		U64;
typedef uint32_t		U32;
typedef uint16_t		U16;
typedef uint8_t			U8;
typedef unsigned int	U4;
typedef unsigned short	U2;
typedef int64_t			I64;
typedef int32_t			I32;
typedef int16_t			I16;
typedef int8_t			I8;
typedef int				I4;
typedef short			I2;
typedef					U64 UTC;
typedef					U8 MAC[6];
typedef					U32 IP4;

struct TIME_INFO {
	U32 YYYY, MM, DD, w, hh, mm, ss, ns;
	TIME_INFO() : YYYY(), MM(), DD(), hh(), mm(), ss(), ns(), w() {}
};
void unpack_utc(TIME_INFO& ti, U64 utc);
void getmac(MAC& Mac, char * iface);
void getip4(IP4& ip, char * iface);


template <typename T> void arr_add(T*& items, int& nItems, T item);
template <typename T> int arr_find(T*& items, int& nItems, T item);
template <typename T> void arr_cut_index(T*& items, int& nItems, int index);
template <typename T> void arr_add_to_set(T*& items, int& nItems, T item);
template <typename T> void arr_remove(T*& items, int& nItems, T item);
template <typename T> void arr_free(T*& items, int& nItems);

U64 nanotime();
void stdout_printf(char* fmt, ...);
void print(const char* fmt, ...);

int str2int(int& dst, char* src);
int str2ip4(const char* dst, IP4 ip);
int ip42str(char* dst, IP4 ip);
int utc2str(char* dst, int cbDstMax, U64 utc);
int mac2str(char* dst, MAC mac);
bool str2mac(MAC& dst, char* src, int cbSrc = -1);



#endif


#endif