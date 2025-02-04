/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Intel MIC Platform Software Stack (MPSS)
 *
 * Copyright(c) 2013 Intel Corporation.
 *
 * Intel MIC User Space Tools.
 */
#ifndef _MPSSD_H_
#define _MPSSD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <libgen.h>
#include <pthread.h>
#include <linux/stdarg.h>
#include <time.h>
#include <errno.h>
#include <sys/dir.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <limits.h>
#include <syslog.h>
#include <getopt.h>
#include <net/if.h>
#include <linux/if_tun.h>
#include <linux/virtio_ids.h>

#define MICSYSFSDIR "/sys/class/mic"
#define LOGFILE_NAME "/var/log/mpssd"
#define PAGE_SIZE 4096

struct mic_console_info {
	pthread_t       console_thread;
	int		virtio_console_fd;
	void		*console_dp;
};

struct mic_net_info {
	pthread_t       net_thread;
	int		virtio_net_fd;
	int		tap_fd;
	void		*net_dp;
};

struct mic_virtblk_info {
	pthread_t       block_thread;
	int		virtio_block_fd;
	void		*block_dp;
	volatile sig_atomic_t	signaled;
	char		*backend_file;
	int		backend;
	void		*backend_addr;
	long		backend_size;
};

struct mic_info {
	int		id;
	char		*name;
	pthread_t       config_thread;
	pthread_t       init_thread;
	pid_t		pid;
	struct mic_console_info	mic_console;
	struct mic_net_info	mic_net;
	struct mic_virtblk_info	mic_virtblk;
	int		restart;
	int		boot_on_resume;
	struct mic_info *next;
};

__attribute__((format(printf, 1, 2)))
void mpsslog(char *format, ...);
char *readsysfs(char *dir, char *entry);
int setsysfs(char *dir, char *entry, char *value);
#endif
