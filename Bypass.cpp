#include <stdio.h>
#include <conio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <thread>

int handle;
typedef char PACKAGENAME;
long int get_module_base(int pid, const char *module_name)
{
	FILE *fp;
	long addr = 0;
	char *pch;
	char filename[32];
	char line[1024];
	snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
	fp = fopen(filename, "r");
	if (fp != NULL)
	{
		while (fgets(line, sizeof(line), fp))
		{
			if (strstr(line, module_name))
			{
				pch = strtok(line, "-");
				addr = strtoul(pch, NULL, 16);
				break;
			}
		}
		fclose(fp);
	}
	return addr;
}

int FPSCHEATS_FLOAT(long int addr, float value)
{
	pwrite64(handle, &value, 4, addr);
	return 0;
}

int FPSCHEATS_DWORD(long int addr, int value)
{
	pwrite64(handle, &value, 4, addr);
	return 0;
}

int getPID(PACKAGENAME * PackageName)
{
	DIR *dir = NULL;
	struct dirent *ptr = NULL;
	FILE *fp = NULL;
	char filepath[256];
	char filetext[128];
	dir = opendir("/proc");
	if (NULL != dir)
	{
		while ((ptr = readdir(dir)) != NULL)
		{

			if ((strcmp(ptr->d_name, ".") == 0) || (strcmp(ptr->d_name, "..") == 0))
				continue;
			if (ptr->d_type != DT_DIR)
				continue;
			sprintf(filepath, "/proc/%s/cmdline", ptr->d_name);
			fp = fopen(filepath, "r");
			if (NULL != fp)
			{
				fgets(filetext, sizeof(filetext), fp);
				if (strcmp(filetext, PackageName) == 0)
				{

					break;
				}
				fclose(fp);
			}
		}
	}
	if (readdir(dir) == NULL)
	{
		return 0;
	}
	closedir(dir);
	return atoi(ptr->d_name);
}


int main(int argc, char **argv)
{
	int gs;
    void *jg;
	FILE *fp;
	char ch, wjm[51];
	if (!(fp = fopen("/storage/emulated/0/", "r"))) //Verify that the folder exists

	{
		
	}

		int ipid = getPID("com.tencent.ig");
		if (ipid == 0)
		{
			ipid = getPID("com.pubg.krmobile");
			if (ipid == 0)
			{
				ipid = getPID("com.rekoo.pubgm");
				if (ipid == 0)
				{
					ipid = getPID("com.pubg.imobile");
					if (ipid == 0)
					{		
						puts("GAME NOT RUNNING");				
                        exit(1);
					}
				}
			}
		}



	char lj[64];
	sprintf(lj, "/proc/%d/mem", ipid);
	handle = open(lj, O_RDWR);
	if (handle == -1)
	{
		puts("ERROR");
		exit(1);
	}
	puts("BLOCKADE CHEAT");

char mnamn[] = "libanogs.so";
long int libanogs = get_module_base(ipid, mnamn);

FPSCHEATS_DWORD(libanogs + 0x385774, 0);
FPSCHEATS_DWORD(libanogs + 0x13F814, 0);
FPSCHEATS_DWORD(libanogs + 0x347B80, 0);
FPSCHEATS_DWORD(libanogs + 0x34F070, 0);
FPSCHEATS_DWORD(libanogs + 0x3882E4, 0);
FPSCHEATS_DWORD(libanogs + 0x34E390, 0);
FPSCHEATS_DWORD(libanogs + 0xC7AD0, 0);
FPSCHEATS_DWORD(libanogs + 0xC78F0, 0);
FPSCHEATS_DWORD(libanogs + 0x326ED8, 0);
FPSCHEATS_DWORD(libanogs + 0x34E55C, 0);


	close(handle);
	return 0;
}

