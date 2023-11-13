#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

/* die:输出错误信息 */
void
die(char *fmt, ...)	// 参数数目可变
{
    va_list a;	// C语言中解决变参问题的定义的一个类型
    va_start(a, fmt);
    vfprintf(stderr, fmt, a);
    va_end(a);
    exit(1);
}

void print_name_pid(pid_t pid)
{
    char name[PATH_MAX];
    int c, i = 0;
    FILE *f;

    sprintf(name, "/proc/%ld/cmdline", (long) pid);
    f = fopen(name, "r");
    if(!f) die("%s: %s\n", name, strerror(errno));
    while((c = getc(f)) != EOF && c != 0)
	name[i++] = c;
    name[i] = '\0';
    printf("%s(%ld)\n", name, (long)pid);	// 输出程序名称
    fclose(f);
}

void print_maps(pid_t pid)
{
    char fname[PATH_MAX];
    unsigned long writable = 0, total = 0, shared = 0;
    FILE *f;

    sprintf(fname, "/proc/%ld/smaps", (long)pid);
    f = fopen(fname, "r");

    if(!f)
	die("%s: %s\n", fname, strerror(errno));
	printf("地址 Dirty Mode/Perm 偏移量 设备  Inode Size Rss Pss Referenced Anonymous LazyFree ShmemPmdMapped FilePmdMapped Shared_Hugetlb Private_Hugetlb Swap SwapPss Locked THPeligible Mapping\n");
    while(!feof(f)) {		
	char buf[PATH_MAX+100], perm[5], dev[6], mapname[PATH_MAX];
	// 地址、权限、映射文件所属设备号、映射的文件名
	unsigned long begin, end, size, inode, foo,Size[24];
	int n;
	for(int i=1;i<=23;i++){
	if(fgets(buf, sizeof(buf), f) == 0)
	    break;
	if(i==1){
	mapname[0] = '\0';
	sscanf(buf, "%lx-%lx %4s %lx %5s %ld %s", &begin, &end, perm,
		&foo, dev, &inode, mapname);	// *
	size = end - begin;
	total += size;
	}
	if(i>=2&&i<=21)
	{
		char tempchar[1000];
		sscanf(buf,"%s%ld%s",tempchar,&Size[i],tempchar);
	}
	if(i==22)
	{
		char tempchar[1000];
		sscanf(buf,"%s%ld",tempchar,&Size[i]);
	}
	if(i==23)
	{
		char tempchar[1000];
		//sscanf(buf,"%s%ld",tempchar,&Size[i]);
	}
	 }
	if(perm[3] == 'p') {
	    if(perm[1] == 'w')
		writable += size;
	} else if(perm[3] == 's')
	    shared += size;
	else
	    die("unable to parse permission string: '%s'\n", perm);
	unsigned long sumDirty=0;
	for(int j=7;j<=10;j++)
	sumDirty+=Size[j];
	n = printf("%08lx ", begin);
	n += printf("%ld %*s %s %lx %s %ld ",sumDirty, 22-n, "", perm,foo, dev, inode);
	printf("%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld ",Size[2],Size[5],Size[6],Size[11],Size[12],Size[13],Size[15],Size[16],Size[17],Size[18],Size[19],Size[20],Size[21],Size[22]);
	printf("%*s %s\n", 44-n, "", mapname);
    }

    printf("mapped:   %ld KB writable/private: %ld KB shared: %ld KB\n",
	    total/1024, writable/1024, shared/1024);
    fclose(f);
}

pid_t parse_pid(char *p)
{
    while(!isdigit(*p) && *p)
	p++;
    return strtol(p, 0, 0);
}

int main(int argc, char **argv)
{
    int i;

    if(argc < 2)
	die("usage: %s -X [pid|/proc/pid] ...\n", argv[0]);
    for(i=2; argv[i]; i++) {
	char *ppid;
	pid_t pid;

	ppid = argv[i];
	pid = parse_pid(ppid);	// 解析pid
	print_name_pid(pid);
	print_maps(pid);
    }
    return 0;
}
