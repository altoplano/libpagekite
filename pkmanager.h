/******************************************************************************
pkmanager.h - A manager for multiple pagekite connections.

This file is Copyright 2011, 2012, The Beanstalks Project ehf.

This program is free software: you can redistribute it and/or modify it under
the terms of the  GNU  Affero General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option) any
later version.

This program is distributed in the hope that it will be useful,  but  WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more
details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see: <http://www.gnu.org/licenses/>

******************************************************************************/

#define PARSER_BYTES_MIN   1 * 1024
#define PARSER_BYTES_MAX   8 * 1024  /* <= CONN_IO_BUFFER_SIZE */

#define PK_HOUSEKEEPING_INTERVAL 10  /* Seconds */

struct pk_conn;
struct pk_frontend;
struct pk_backend_conn;
struct pk_manager;

#define CONN_IO_BUFFER_SIZE   8 * 1024
#define CONN_STATUS_UNKNOWN   0x0000
#define CONN_STATUS_READABLE  0x0001
#define CONN_STATUS_WRITEABLE 0x0002
#define CONN_STATUS_ALLOCATED 0x0004
struct pk_conn {
  int               status;
  int               sockfd;
  time_t            activity;
  int               in_buffer_bytes_free;
  unsigned char     in_buffer[CONN_IO_BUFFER_SIZE];
  int               out_buffer_bytes_free;
  unsigned char     out_buffer[CONN_IO_BUFFER_SIZE];
  ev_io             watch_r;
  ev_io             watch_w;
};

#define FE_STATUS_DOWN 0x0010
#define FE_STATUS_UP   0x0020
struct pk_frontend {
  char*                   fe_hostname;
  int                     fe_port;
  int                     priority;
  struct pk_conn          conn;
  struct pk_parser*       parser;
  struct pk_manager*      manager;
  int                     request_count;
  struct pk_kite_request* requests;
};

#define BE_STATUS_EOF_READ      0x0100
#define BE_STATUS_EOF_WRITE     0x0200
#define BE_STATUS_EOF_THROTTLED 0x0400
struct pk_backend_conn {
  char                sid[8];
  struct pk_frontend* frontend;
  struct pk_pagekite* kite;
  struct pk_conn*     conn;
};

#define MIN_KITE_ALLOC  1
#define MIN_FE_ALLOC    1
#define MIN_CONN_ALLOC 20
struct pk_manager {
  int                      kite_count;
  struct pk_pagekite*      kites; 
  int                      frontend_count;
  struct pk_frontend*      frontends;   
  int                      be_conn_count;
  struct pk_backend_conn*  be_conns;   
  int                      buffer_bytes_free;
  unsigned char*           buffer;
  unsigned char*           buffer_base;
  struct ev_loop*          loop;
  ev_timer                 timer;
};

struct pk_manager*  pk_manager_init(struct ev_loop*,
                                    int, unsigned char*, int, int, int);
struct pk_pagekite* pk_add_kite(struct pk_manager*,
                                const char*, const char*, const char*,
                                int, int);
struct pk_frontend* pk_add_frontend(struct pk_manager*,
                                    const char*, int, int);

int                 pkmanager_test(void);

