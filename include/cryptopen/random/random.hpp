/*
 * libcryptopen - C++ portable OpenSSL cryptographic wrapper library.
 * Copyright (C) 2010-2011 Julien Kauffmann <julien.kauffmann@freelan.org>
 *
 * This file is part of libcryptopen.
 *
 * libcryptopen is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * libcryptopen is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 *
 * If you intend to use libcryptopen in a commercial software, please
 * contact me : we may arrange this for a small fee or no fee at all,
 * depending on the nature of your project.
 */

/**
 * \file random.hpp
 * \author Julien Kauffmann <julien.kauffmann@freelan.org>
 * \brief Randomization helper functions.
 */

#ifndef CRYPTOPEN_RANDOM_RANDOM_HPP
#define CRYPTOPEN_RANDOM_RANDOM_HPP

#include "../error/cryptographic_exception.hpp"

#include <openssl/rand.h>

namespace cryptopen
{
	namespace random
	{
		/**
		 * \brief Set the randomization engine.
		 * \param engine The randomization engine.
		 *
		 * On error, a cryptographic_exception is thrown.
		 */
		void set_randomization_engine(ENGINE* engine);

		/**
		 * \brief Get truly random bytes.
		 * \param buf The buffer to fill with the random bytes. Its content will be mixed in the enthropy pool unless disabled at OpenSSL compile time.
		 * \param buf_len The number of random bytes to request. buf must be big enough to hold the data.
		 * \see get_pseudo_random_bytes
		 *
		 * If the PRNG was not seeded with enough randomness, the call fails and a cryptographic_exception is thrown.
		 */
		void get_random_bytes(void* buf, size_t buf_len);

		/**
		 * \brief Get pseudo random bytes.
		 * \param buf The buffer to fill with the random bytes. Its content will be mixed in the enthropy pool unless disabled at OpenSSL compile time.
		 * \param buf_len The number of random bytes to request. buf must be big enough to hold the data.
		 * \return true if the generated numbers are cryptographically strong, false otherwise.
		 * \see get_random_bytes
		 *
		 * Do not use the resulting bytes for critical cryptographic purposes (like key generation). If require truly random bytes, see get_random_bytes().
		 *
		 * If the PRNG was not seeded with enough randomness, the call fails and a cryptographic_exception is thrown.
		 */
		bool get_pseudo_random_bytes(void* buf, size_t buf_len);

		inline void set_randomization_engine(ENGINE* engine)
		{
			error::throw_error_if_not(RAND_set_rand_engine(engine));
		}
		
		inline void get_random_bytes(void* buf, size_t buf_len)
		{
			error::throw_error_if_not(RAND_bytes(static_cast<unsigned char*>(buf), static_cast<int>(buf_len)) == 1);
		}
		
		inline bool get_pseudo_random_bytes(void* buf, size_t buf_len)
		{
			int result = RAND_pseudo_bytes(static_cast<unsigned char*>(buf), static_cast<int>(buf_len));

			error::throw_error_if(result < 0);

			return (result == 1);
		}
	}
}

#endif /* CRYPTOPEN_RANDOM_RANDOM_HPP */