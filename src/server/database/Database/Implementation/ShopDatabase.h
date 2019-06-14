/*
 * Copyright (C) 2008-2018 TrinityCore <https://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SHOPDATABASE_H
#define _SHOPDATABASE_H

#include "MySQLConnection.h"

enum ShopDatabaseStatements : uint32
{
    /*  Naming standard for defines:
        {DB}_{SEL/INS/UPD/DEL/REP}_{Summary of data changed}
        When updating more than one field, consider looking at the calling function
        name for a suiting suffix.
    */

    SHOP_SEL_DONATIONS_POINTS,
    SHOP_UPD_DONATIONS_POINTS,
    SHOP_INS_DONATIONS_REWARD_LOG,
    SHOP_SEL_DONATIONS_COOLDOWN,
    SHOP_REP_DONATIONS_BONUS_COOLDOWN,
    SHOP_INS_DONATIONS_BONUS,

    MAX_SHOPDATABASE_STATEMENTS
};

class TC_DATABASE_API ShopDatabaseConnection : public MySQLConnection
{
public:
    typedef ShopDatabaseStatements Statements;

    //- Constructors for sync and async connections
    ShopDatabaseConnection(MySQLConnectionInfo& connInfo);
    ShopDatabaseConnection(ProducerConsumerQueue<SQLOperation*>* q, MySQLConnectionInfo& connInfo);
    ~ShopDatabaseConnection();

    //- Loads database type specific prepared statements
    void DoPrepareStatements() override;
};

#endif
