/*******************************************************************************
 * Copyright (c) 2016 Guilherme M. Ferreira <guilherme.maciel.ferreira@gmail.com>
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
 *    Guilherme M. Ferreira - initial implementation and documentation
 *    Frank Pagliughi - added copy & move operations
 *******************************************************************************/

#include "mqtt/will_options.h"
#include <utility>
#include <cstring>

namespace mqtt {

/////////////////////////////////////////////////////////////////////////////

will_options::will_options()
		: opts_(MQTTAsync_willOptions_initializer)
{
}

will_options::will_options(const std::string& top,
						   const void *payload,
						   size_t payload_len,
						   int qos,
						   bool retained)
		: opts_(MQTTAsync_willOptions_initializer), topic_(top),
			payload_(static_cast<const char *>(payload), payload_len)
{
	opts_.topicName = topic_.c_str();
	opts_.message = payload_.c_str();
	opts_.qos = qos;
	opts_.retained = retained;
}

will_options::will_options(const topic& top,
						   const void *payload,
						   size_t payload_len,
						   int qos, bool retained)
		: will_options(top.get_name(), payload, payload_len, qos, retained)
{
}


will_options::will_options(const std::string& top,
						   const std::string& payload,
						   int qos, bool retained)
		: opts_(MQTTAsync_willOptions_initializer),
			topic_(top), payload_(payload)
{
	opts_.topicName = topic_.c_str();
	opts_.message = payload_.c_str();
	opts_.qos = qos;
	opts_.retained = retained;
}

will_options::will_options(const std::string& top, const message& msg)
	: will_options(top, msg.get_payload(), msg.get_qos(), msg.is_retained())
{
}

will_options::will_options(const will_options& opt)
		: opts_(opt.opts_), topic_(opt.topic_), payload_(opt.payload_)
{
	opts_.topicName = topic_.c_str();
	opts_.message = payload_.c_str();
}

will_options::will_options(will_options&& opt)
		: opts_(opt.opts_), topic_(std::move(opt.topic_)),
			payload_(std::move(opt.payload_))
{
	// OPTIMIZE: We probably don't need to do the following,
	// but just to be safe
	std::memset(&opt.opts_, 0, sizeof(MQTTAsync_willOptions));
	opts_.topicName = topic_.c_str();
	opts_.message = payload_.c_str();
}

will_options& will_options::operator=(const will_options& rhs)
{
	if (&rhs != this) {
		std::memcpy(&opts_, &rhs.opts_, sizeof(MQTTAsync_willOptions));

		topic_ = rhs.topic_;
		payload_ = rhs.payload_;

		opts_.topicName = topic_.c_str();
		opts_.message = payload_.c_str();
	}
	return *this;
}

will_options& will_options::operator=(will_options&& rhs)
{
	if (&rhs != this) {
		std::memcpy(&opts_, &rhs.opts_, sizeof(MQTTAsync_willOptions));

		topic_ = std::move(rhs.topic_);
		payload_ = std::move(rhs.payload_);

		// OPTIMIZE: We probably don't need to do the following,
		// but just to be safe
		std::memset(&rhs.opts_, 0, sizeof(MQTTAsync_willOptions));

		opts_.topicName = topic_.c_str();
		opts_.message = payload_.c_str();
	}
	return *this;
}

void will_options::set_topic(const std::string& top)
{
	topic_ = top;
	opts_.topicName = topic_.c_str();
}

void will_options::set_payload(const std::string& msg)
{
	payload_ = msg;
	opts_.message = payload_.c_str();
}

/////////////////////////////////////////////////////////////////////////////

} // end namespace mqtt

