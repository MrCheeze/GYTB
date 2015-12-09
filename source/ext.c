#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <3ds.h>

u8 null_smdh[0x36C0] = {0};

Result CreateExtSaveData(u32 extdataID)
{
	Handle* handle = fsGetSessionHandle();

	u32* cmdbuf = getThreadCommandBuffer();

	u32 directory_limit = 1000;
	u32 file_limit = 1000;
	
	cmdbuf[0] = 0x08300182;
	cmdbuf[1] = mediatype_SDMC;
	cmdbuf[2] = extdataID;
	cmdbuf[3] = 0;
	cmdbuf[4] = 0x36C0;
	cmdbuf[5] = directory_limit;
	cmdbuf[6] = file_limit;
	cmdbuf[7] = (0x36C0 << 4) | 0xA;
	cmdbuf[8] = (u32) &null_smdh;

	Result ret = 0;
	if((ret = svcSendSyncRequest(*handle)))
		return ret;

	return cmdbuf[1];
}

Result DeleteExtSaveData(u32 extdataID)
{
	Handle* handle = fsGetSessionHandle();

	u32* cmdbuf = getThreadCommandBuffer();
	
	cmdbuf[0] = 0x08350080;
	cmdbuf[1] = mediatype_SDMC;
	cmdbuf[2] = extdataID;

	Result ret = 0;
	if((ret = svcSendSyncRequest(*handle)))
		return ret;

	return cmdbuf[1];
}