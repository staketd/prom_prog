//
// Created by Pavel Akhtyamov on 02.05.2020.
//

#include "WeatherTestCase.h"
#include "WeatherMock.h"
#include <exception>

using testing::Return;
using testing::Throw;

TEST_F(WeatherTestCase, test1) {
    WeatherMock mock;
    std::vector<float> diffs = {-5, -1, 0, 1, 5};
    std::vector<std::string> str_res = {"much colder", "colder", "the same", "warmer", "much warmer"};
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_CALL(mock, GetTomorrowTemperature(std::string("city"))).Times(1).WillRepeatedly(Return(0));
        EXPECT_CALL(mock, GetTemperature(std::string("city"))).Times(1).WillRepeatedly(Return(-diffs[i]));
        ASSERT_EQ(mock.GetTomorrowDiff(std::string("city")),
                  "The weather in city tomorrow will be " + str_res[i] + " than today.");
    }
}

TEST_F(WeatherTestCase, TestNoMock) {
    Weather weather;
    ASSERT_NO_THROW(weather.SetApiKey(api_key_));
    ASSERT_NO_THROW(weather.GetTomorrowDiff("Moscow"));
}

TEST_F(WeatherTestCase, TestWithoutApiKey) {
    Weather weather;
    ASSERT_ANY_THROW(weather.GetTomorrowDiff("London"));
}

TEST_F(WeatherTestCase, TestDifferenceString) {
    WeatherMock mock;
    EXPECT_CALL(mock, GetTemperature("London")).Times(1).WillRepeatedly(Return(10.0));
    EXPECT_CALL(mock, GetTemperature("Moscow")).Times(1).WillRepeatedly(Return(5.0));
    ASSERT_EQ(mock.GetDifferenceString("London", "Moscow"), "Weather in London is warmer than in Moscow by 5 degrees");

    EXPECT_CALL(mock, GetTemperature("London")).Times(1).WillRepeatedly(Return(5.0));
    EXPECT_CALL(mock, GetTemperature("Moscow")).Times(1).WillRepeatedly(Return(10.0));
    ASSERT_EQ(mock.GetDifferenceString("London", "Moscow"), "Weather in London is colder than in Moscow by 5 degrees");
}

TEST_F(WeatherTestCase, wut) {
    WeatherMock mock;
    EXPECT_CALL(mock, GetTemperature(testing::_)).Times(1).WillRepeatedly(Throw(std::runtime_error("")));
    ASSERT_THROW(mock.GetDifferenceString("Moscow", "Izhevsk"), std::runtime_error);
}