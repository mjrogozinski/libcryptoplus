#include <cryptopen/hash/hmac_context.hpp>

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

template <typename T>
std::string to_hex(const T& begin, const T& end)
{
	std::ostringstream oss;

	for (T i = begin; i != end; ++i)
	{
		oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(*i);
	}

	return oss.str();
}

std::string to_hex(const void* buf, size_t buf_len)
{
	return to_hex(static_cast<const unsigned char*>(buf), static_cast<const unsigned char*>(buf) + buf_len);
}

void hmac(const std::string& name, const std::string& key, const std::string& data, const EVP_MD* md)
{
	cryptopen::hash::hmac_context ctx;

	ctx.initialize(key.c_str(), key.size(), md);
	ctx.update(data.c_str(), data.size());
	std::vector<unsigned char> hmac = ctx.finalize<unsigned char>();

	std::cout << name << ": " << to_hex(hmac.begin(), hmac.end()) << std::endl;
}

int main()
{
	std::cout << "HMAC sample" << std::endl;
	std::cout << "===========" << std::endl;
	std::cout << std::endl;

	const std::string key = "this is a very long and secret key";
	const std::string data = "some data from which we will compute the HMAC";

	std::cout << "Key: " << key << std::endl;
	std::cout << "Data: " << data << std::endl;
	std::cout << std::endl;

	hmac("MD5", key, data, EVP_md5());
	hmac("SHA", key, data, EVP_sha());
	hmac("SHA1", key, data, EVP_sha1());
	hmac("SHA256", key, data, EVP_sha256());
	hmac("DSS", key, data, EVP_dss());
	hmac("DSS1", key, data, EVP_dss1());
	hmac("MDC2", key, data, EVP_mdc2());
	hmac("RIPEMD160", key, data, EVP_ripemd160());

	return EXIT_SUCCESS;
}