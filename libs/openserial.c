//      openserial.c
//
//      Copyright 2011 bruno <bruno@nasty>
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
//
//

#include <haabnexa.h>
#include <openserial.h>


int openserial(char *cPort)
{
	int fd; //File descriptor

	fd = open(cPort, O_NOCTTY | O_NDELAY | O_RDWR);
	if (fd == -1)
	{
		//Error opening port
		perror("open_port: Unable to open /dev/ttyS0");
	}
	else
		fcntl(fd, F_SETFL, 0);

	return (fd);
}
