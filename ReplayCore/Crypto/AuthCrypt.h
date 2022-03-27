/**
 * MaNGOS is a full featured server for World of Warcraft, supporting
 * the following clients: 1.12.x, 2.4.3, 3.3.5a, 4.3.4a and 5.4.8
 *
 * Copyright (C) 2005-2014  MaNGOS project <http://getmangos.eu>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * World of Warcraft, and all World of Warcraft or Warcraft art, images,
 * and lore are copyrighted by Blizzard Entertainment, Inc.
 */

#ifndef MANGOS_H_AUTHCRYPT
#define MANGOS_H_AUTHCRYPT

#include "../Defines/Common.h"
#include <openssl/rc4.h>
#include <vector>

class BigNumber;

class AuthCrypt
{
    public:
        AuthCrypt();
        ~AuthCrypt();

        static size_t const CRYPTED_SEND_LEN = 4;
        static size_t const CRYPTED_RECV_LEN = 6;

        void InitVanilla(BigNumber* K);
        void InitTBC(BigNumber* K);
        void InitWOTLK(BigNumber* K);

        void SetKey(std::vector<uint8> const& key);
        void SetKey(uint8* key, size_t len);

        void DecryptRecv(uint8*, size_t);
        void EncryptSend(uint8*, size_t);

        bool IsInitialized() { return m_isInitialized; }

        static void GenerateKey(uint8*, BigNumber*);

    private:
        bool m_wotlk = false;
        RC4_KEY m_clientWotlkDecryptKey;
        RC4_KEY m_serverWotlkEncryptKey;

        std::vector<uint8> m_key;
        uint8 m_send_i, m_send_j, m_recv_i, m_recv_j;
        bool m_isInitialized;
};

#endif
