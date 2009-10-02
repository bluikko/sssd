/*
    Authors:
        Jakub Hrozek <jhrozek@redhat.com>
        Simo Sorce <ssorce@redhat.com>

    Copyright (C) 2009 Red Hat

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef __TOOLS_UTIL_H__
#define __TOOLS_UTIL_H__

#include <popt.h>

#include "util/sssd-i18n.h"

#define CHECK_ROOT(val, prg_name) do { \
    val = getuid(); \
    if (val != 0) { \
        DEBUG(1, ("Running under %d, must be root\n", val)); \
        ERROR("%s must be run as root\n", prg_name); \
        val = EXIT_FAILURE; \
        goto fini; \
    } \
} while(0)

struct tools_ctx {
    struct tevent_context *ev;
    struct confdb_ctx *confdb;
    struct sysdb_ctx *sysdb;

    struct sss_names_ctx *snctx;
    struct sss_domain_info *local;

    struct ops_ctx *octx;

    struct sysdb_handle *handle;
    bool transaction_done;
    int error;
};

int init_sss_tools(struct tools_ctx **_tctx);

void usage(poptContext pc, const char *error);

int set_locale(void);


int parse_name_domain(struct tools_ctx *tctx,
                      const char *fullname);

int id_in_range(uint32_t id,
                struct sss_domain_info *dom);

int parse_groups(TALLOC_CTX *mem_ctx,
                 const char *optstr,
                 char ***_out);

int parse_group_name_domain(struct tools_ctx *tctx,
                            char **groups);

int check_group_names(struct tools_ctx *tctx,
                      char **grouplist,
                      char **badgroup);

#endif  /* __TOOLS_UTIL_H__ */
