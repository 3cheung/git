#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

// 判断前 len = len1 < len2 ? len1 : len2 是否相同
static int cache_name_compare(const char *name1, int len1, const char *name2, int len2)
{
	int len = len1 < len2 ? len1 : len2;
    printf("len: %d\n",len);
	int cmp;
	//memcmp() 存储区 str1 和存储区 str2 的前 n 个字节进行比较
	cmp = memcmp(name1, name2, len);
    printf("cmp: %d\n",cmp);
	if (cmp) // 不相同则返回cmp
		return cmp;
	if (len1 < len2) // 长度小于则返回 -1
		return -1;
	if (len1 > len2)
		return 1;
	return 0;
}
int main(){
    char *name1 = "aaaab";
    char *name2 = "aaaaa";
    int cmp = memcmp(name1, name2, 2);
    printf("%d\n",cmp);
    int r = cache_name_compare(name1,2,name2,4);
    printf("返回值：%d\n",r);

	int next = 10;
	int a = -next-1;
	int b = -a -1;
	printf("a：",a);

	char *path = "./cache.h";
	int fd;
	fd = open(path, O_RDONLY);
	printf("fd:%d",fd);
	struct stat st;
	if (fstat(fd, &st) < 0) { //由文件描述词取得文件状态
		
	}
	printf("fd:%d",st.st_size);
    return 0;
}