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

#include "AuthCrypt.h"
#include "BigNumber.h"
#include "Hmac.h"

#define SEED_KEY_SIZE 16

AuthCrypt::AuthCrypt()
{
    m_wotlk = false;
    m_isInitialized = false;
}

AuthCrypt::~AuthCrypt()
{
}

void AuthCrypt::InitVanilla(BigNumber* K)
{
    SetKey(K->AsByteArray());
    m_send_i = m_send_j = m_recv_i = m_recv_j = 0;
    m_isInitialized = true;
}

void AuthCrypt::InitTBC(BigNumber* K)
{
    uint8* key = new uint8[SHA_DIGEST_LENGTH];
    uint8 recvSeed[SEED_KEY_SIZE] = { 0x38, 0xA7, 0x83, 0x15, 0xF8, 0x92, 0x25, 0x30, 0x71, 0x98, 0x67, 0xB1, 0x8C, 0x4, 0xE2, 0xAA };
    HmacHash recvHash((uint8*)recvSeed, SEED_KEY_SIZE);
    recvHash.UpdateBigNumber(K);
    recvHash.Finalize();
    memcpy(key, recvHash.GetDigest(), SHA_DIGEST_LENGTH);
    m_key.resize(SHA_DIGEST_LENGTH);
    std::copy(key, key + SHA_DIGEST_LENGTH, m_key.begin());
    delete[] key;

    m_send_i = m_send_j = m_recv_i = m_recv_j = 0;
    m_isInitialized = true;
}

void AuthCrypt::InitWOTLK(BigNumber* K)
{
    static const uint8_t send[SEED_KEY_SIZE] = { 0xC2, 0xB3, 0x72, 0x3C, 0xC6, 0xAE, 0xD9, 0xB5, 0x34, 0x3C, 0x53, 0xEE, 0x2F, 0x43, 0x67, 0xCE };
    static const uint8_t recv[SEED_KEY_SIZE] = { 0xCC, 0x98, 0xAE, 0x04, 0xE8, 0x97, 0xEA, 0xCA, 0x12, 0xDD, 0xC0, 0x93, 0x42, 0x91, 0x53, 0x57 };

    uint8_t encryptHash[SHA_DIGEST_LENGTH];
    uint8_t decryptHash[SHA_DIGEST_LENGTH];

    uint8_t pass[1024];
    uint32_t mdLength;

    HMAC(EVP_sha1(), send, SEED_KEY_SIZE, K->AsByteArray().data(), 40, decryptHash, &mdLength);
    assert(mdLength == SHA_DIGEST_LENGTH);

    HMAC(EVP_sha1(), recv, SEED_KEY_SIZE, K->AsByteArray().data(), 40, encryptHash, &mdLength);
    assert(mdLength == SHA_DIGEST_LENGTH);

    RC4_set_key(&m_clientWotlkDecryptKey, SHA_DIGEST_LENGTH, decryptHash);
    RC4_set_key(&m_serverWotlkEncryptKey, SHA_DIGEST_LENGTH, encryptHash);

    RC4(&m_serverWotlkEncryptKey, 1024, pass, pass);
    RC4(&m_clientWotlkDecryptKey, 1024, pass, pass);

    m_wotlk = true;
    m_isInitialized = true;
}

void AuthCrypt::DecryptRecv(uint8* data, size_t len)
{
    if (!m_isInitialized)
        return;

    if (!m_wotlk)
    {
        if (len < CRYPTED_RECV_LEN)
            return;

        for (size_t t = 0; t < CRYPTED_RECV_LEN; t++)
        {
            m_recv_i %= m_key.size();
            uint8 x = (data[t] - m_recv_j) ^ m_key[m_recv_i];
            ++m_recv_i;
            m_recv_j = data[t];
            data[t] = x;
        }
    }
    else
        RC4(&m_clientWotlkDecryptKey, (unsigned long)len, data, data);
}

void AuthCrypt::EncryptSend(uint8* data, size_t len)
{
    if (!m_isInitialized)
        return;

    if (!m_wotlk)
    {
        if (len < CRYPTED_SEND_LEN)
            return;

        for (size_t t = 0; t < CRYPTED_SEND_LEN; t++)
        {
            m_send_i %= m_key.size();
            uint8 x = (data[t] ^ m_key[m_send_i]) + m_send_j;
            ++m_send_i;
            data[t] = m_send_j = x;
        }
    }
    else
        RC4(&m_serverWotlkEncryptKey, (unsigned long)len, data, data);
}

void AuthCrypt::SetKey(std::vector<uint8> const& key)
{
    assert(key.size());
    m_key = key;
    if (m_key.empty())
        m_key.resize(1); // temp
}

void AuthCrypt::SetKey(uint8* key, size_t len)
{
    assert(len);
    m_key.resize(len);
    std::copy(key, key + len, m_key.begin());

    if (m_key.empty())
        m_key.resize(1);
}

void AuthCrypt::GenerateKey(uint8* key, BigNumber* bn)
{
    HmacHash hash;
    hash.UpdateBigNumber(bn);
    hash.Finalize();
    memcpy(key, hash.GetDigest(), SHA_DIGEST_LENGTH);
}
