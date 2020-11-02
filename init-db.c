#include "cache.h"

int main(int argc, char **argv)
{
	// 配置统一保存路径
	char *sha1_dir = getenv(DB_ENVIRONMENT), *path;
	int len, i, fd;
 	// 创建 .dircache/ 权限为 700
	if (mkdir(".dircache", 0700) < 0) {
		perror("unable to create .dircache");
		exit(1);
	}

	/*
	 * If you want to, you can share the DB area with any number of branches.
	 * That has advantages: you can save space by sharing all the SHA1 objects.
	 * On the other hand, it might just make lookup slower and messier. You
	 * be the judge.
	 */
	sha1_dir = getenv(DB_ENVIRONMENT);
	if (sha1_dir) {
		struct stat st;
		// stat():返回关于文件的信息,ISDIR()函数的作用是判断一个路径是不是目录
		// 存在统一路径就退出
		if (!stat(sha1_dir, &st) < 0 && S_ISDIR(st.st_mode))
			return;
		fprintf(stderr, "DB_ENVIRONMENT set to bad directory %s: ", sha1_dir);
	}

	/*
	 * The default case is to have a DB per managed directory. 
	 */
	sha1_dir = DEFAULT_DB_ENVIRONMENT;
	fprintf(stderr, "defaulting to private storage area\n");
	len = strlen(sha1_dir);
	if (mkdir(sha1_dir, 0700) < 0) {
		if (errno != EEXIST) {
			perror(sha1_dir);
			exit(1);
		}
	}
	path = malloc(len + 40); // 40 = 8 + 16 + 16 ：'/':8,两个16位的数
	// 把 sha1_dir -> path(长度为len)
	memcpy(path, sha1_dir, len);
	for (i = 0; i < 256; i++) {
		// i 通过 "/%02x" 格式放到 path+len的地址
		sprintf(path+len, "/%02x", i);
		if (mkdir(path, 0700) < 0) {
			if (errno != EEXIST) {
				perror(path);
				exit(1);
			}
		}
	}
	
	return 0;
}
