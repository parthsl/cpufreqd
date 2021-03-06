/*
 *  Copyright (C) 2006-2008  Mattia Dongili <malattia@linux.it>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "cpufreqd_plugin.h"
#include "cpufreqd_acpi.h"
#include "cpufreqd_acpi_ac.h"
#include "cpufreqd_acpi_battery.h"
#include "cpufreqd_acpi_event.h"
#include "cpufreqd_acpi_temperature.h"

/*
 * init default values
 */
static int train_init (void) {
	clog(LOG_CRIT, " Hi\n");
	return 0;
}
static int train_exit (void) {
	clog(LOG_CRIT, "exit\n");
}

static int train_update(void) {
	clog(LOG_CRIT, "update\n");
	return 0;
}

static struct cpufreqd_keyword kw[] = {
	{ .word = "ac", .parse = &train_update, .evaluate = &train_exit },
	{ .word = NULL, .parse = NULL, .evaluate = NULL, .free = NULL }
};

static struct cpufreqd_plugin train = {
	.plugin_name	= "train",	/* plugin_name */
	.keywords	= kw,			/* config_keywords */
	.plugin_init	= &train_init,		/* plugin_init */
	.plugin_exit	= &train_exit,		/* plugin_exit */
	.plugin_update	= &train_update,		/* plugin_update */
	.plugin_conf	= &train_init,
	.plugin_post_conf = &train_init,
};

struct cpufreqd_plugin *create_plugin (void) {
	return &train;
}
