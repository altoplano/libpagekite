/******************************************************************************
pkrelay.h - Logic specific to front-end relays

*******************************************************************************

This file is Copyright 2011-2015, The Beanstalks Project ehf.

This program is free software: you can redistribute it and/or modify it under
the terms of the  GNU Affero General Public License, version 3.0 or above, as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,  but  WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the Apache License for more details.

You should have received a copy of the GNU AGPL along with this program.
If not, see: <http://www.gnu.org/licenses/agpl.html>

Note: For alternate license terms, see the file COPYING.md.

******************************************************************************/

struct pk_listener {
  int lport;
};

struct pk_listener* pkr_add_listener(struct pk_manager*, int);
struct pk_listener* pkr_add_listener_v6(struct pk_manager*, int);
