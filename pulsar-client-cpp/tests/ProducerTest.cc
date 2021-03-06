/**
 * Copyright 2016 Yahoo Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <pulsar/Client.h>
#include <gtest/gtest.h>

#include "../lib/Future.h"
#include "../lib/Utils.h"

using namespace pulsar;

TEST(ProducerTest, producerNotInitialized) {
    Producer producer;

    Message msg = MessageBuilder().setContent("test").build();

    ASSERT_EQ(ResultProducerNotInitialized, producer.send(msg));

    Promise<Result, Message> promise;
    producer.sendAsync(msg, WaitForCallbackValue<Message>(promise));

    Message m;
    ASSERT_EQ(ResultProducerNotInitialized, promise.getFuture().get(m));

    ASSERT_EQ(ResultProducerNotInitialized, producer.close());

    Promise<bool, Result> promiseClose;
    producer.closeAsync(WaitForCallback(promiseClose));

    Result result;
    promiseClose.getFuture().get(result);
    ASSERT_EQ(ResultProducerNotInitialized, result);

    ASSERT_TRUE(producer.getTopic().empty());
}
