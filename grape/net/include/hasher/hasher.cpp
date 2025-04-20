#include "hasher.h"
#include <openssl/evp.h>

std::string toHash::_msg;

std::string toHash::hash(std::string msg) {
    _msg = msg;
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();

    EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr);
    EVP_DigestUpdate(ctx, _msg.c_str(), _msg.size());
    EVP_DigestFinal_ex(ctx, hash, &hash_len);
    EVP_MD_CTX_free(ctx);

    std::string result;
    result.reserve(hash_len * 2);
    static const char hex_digits[] = "0123456789abcdef";
    for (unsigned int i = 0; i < hash_len; ++i) {
        result.push_back(hex_digits[(hash[i] >> 4) & 0xF]);
        result.push_back(hex_digits[hash[i] & 0xF]);
    }
    return result;
}
