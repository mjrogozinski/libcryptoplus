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
 * \file message_digest_context.cpp
 * \author Julien KAUFFMANN <julien.kauffmann@freelan.org>
 * \brief A message digest context class.
 */

#include "hash/message_digest_context.hpp"

#include <cassert>

namespace cryptopen
{
	namespace hash
	{
		void message_digest_context::initialize(const EVP_MD* md, ENGINE* impl)
		{
			assert(md);

			error::throw_error_if_not(EVP_DigestInit_ex(&m_ctx, md, impl));

			m_md = md;
		}

		size_t message_digest_context::finalize(void* md, size_t len)
		{
			assert(md);

			unsigned int ilen = static_cast<unsigned int>(len);

			error::throw_error_if_not(EVP_DigestFinal_ex(&m_ctx, static_cast<unsigned char*>(md), &ilen));

			return ilen;
		}
	}
}
