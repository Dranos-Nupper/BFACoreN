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

#include "ShopDatabase.h"
#include "PreparedStatement.h"

void ShopDatabaseConnection::DoPrepareStatements()
{
    if (!m_reconnecting)
        m_stmts.resize(MAX_SHOPDATABASE_STATEMENTS);

    PrepareStatement(SHOP_SEL_DONATIONS_POINTS,         "SELECT nbPoints FROM points WHERE account_id = ?", CONNECTION_SYNCH);
    PrepareStatement(SHOP_UPD_DONATIONS_POINTS,         "SELECT 1", CONNECTION_ASYNC);
    PrepareStatement(SHOP_INS_DONATIONS_REWARD_LOG,     "SELECT 1", CONNECTION_ASYNC);
    PrepareStatement(SHOP_SEL_DONATIONS_COOLDOWN,       "SELECT 1 FROM achats WHERE id = ? AND account_id = ?", CONNECTION_SYNCH);
    PrepareStatement(SHOP_REP_DONATIONS_BONUS_COOLDOWN, "SELECT 1", CONNECTION_ASYNC);
    PrepareStatement(SHOP_INS_DONATIONS_BONUS,          "SELECT 1", CONNECTION_ASYNC);
}

ShopDatabaseConnection::ShopDatabaseConnection(MySQLConnectionInfo& connInfo) : MySQLConnection(connInfo)
{
}

ShopDatabaseConnection::ShopDatabaseConnection(ProducerConsumerQueue<SQLOperation*>* q, MySQLConnectionInfo& connInfo) : MySQLConnection(q, connInfo)
{
}

ShopDatabaseConnection::~ShopDatabaseConnection()
{
}
