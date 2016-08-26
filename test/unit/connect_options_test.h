// connect_options_test.h
// Unit tests for the connect_options class in the Paho MQTT C++ library.

/*******************************************************************************
 * Copyright (c) 2016 Frank Pagliughi <fpagliughi@mindspring.com>
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Frank Pagliughi - initial implementation and documentation
 *******************************************************************************/

#ifndef __mqtt_connect_options_test_h
#define __mqtt_connect_options_test_h

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "mqtt/connect_options.h"

/////////////////////////////////////////////////////////////////////////////

class connect_options_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( connect_options_test );
	CPPUNIT_TEST( test_dflt_constructor );
	CPPUNIT_TEST( test_user_constructor );
	CPPUNIT_TEST( test_set_user );

	CPPUNIT_TEST_SUITE_END();

	const std::string EMPTY_STR;

public:
	void setUp() {}
	void tearDown() {}

	// ----------------------------------------------------------------------

	// Test the default constructor
	void test_dflt_constructor() {
		mqtt::connect_options opts;
		CPPUNIT_ASSERT_EQUAL(EMPTY_STR, opts.get_user_name());
		CPPUNIT_ASSERT_EQUAL(EMPTY_STR, opts.get_password());
	}

	// Test the constructor that takes user/password
	void test_user_constructor() {
		const std::string USER("wally");
		const std::string PASSWD("xyzpdq");

		mqtt::connect_options opts(USER, PASSWD);
		CPPUNIT_ASSERT_EQUAL(USER, opts.get_user_name());
		CPPUNIT_ASSERT_EQUAL(PASSWD, opts.get_password());
	}

	// Test set/get of the user and password.
	void test_set_user() {
		mqtt::connect_options opts;

		const std::string USER("wally");
		const std::string PASSWD("xyzpdq");

		opts.set_user_name(USER);
		opts.set_password(PASSWD);

		CPPUNIT_ASSERT_EQUAL(USER, opts.get_user_name());
		CPPUNIT_ASSERT_EQUAL(PASSWD, opts.get_password());
	}

};

#endif		//  __mqtt_connect_options_test_h


