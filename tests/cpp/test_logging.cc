#include <map>

#include <gtest/gtest.h>
#include <xgboost/logging.h>

namespace xgboost {

TEST(Logging, Basic) {
  std::map<std::string, std::string> args {};
  args["verbosity"] = "0";  // silent
  ConsoleLogger::Configure(args.cbegin(), args.cend());
  testing::internal::CaptureStderr();
  std::string output = testing::internal::GetCapturedStderr();
  ASSERT_EQ(output.length(), 0);

  args["verbosity"] = "3";  // debug
  ConsoleLogger::Configure(args.cbegin(), args.cend());

  testing::internal::CaptureStderr();
  LOG(WARNING) << "Test Log Warning.";
  output = testing::internal::GetCapturedStderr();
  ASSERT_NE(output.find("WARNING"), std::string::npos);

  testing::internal::CaptureStderr();
  LOG(INFO) << "Test Log Info";
  output = testing::internal::GetCapturedStderr();
  ASSERT_NE(output.find("Test Log Info"), std::string::npos);

  testing::internal::CaptureStderr();
  LOG(DEBUG) << "Test Log Debug.";
  output = testing::internal::GetCapturedStderr();
  ASSERT_NE(output.find("DEBUG"), std::string::npos);

  args["silent"] = "True";
  ConsoleLogger::Configure(args.cbegin(), args.cend());
  testing::internal::CaptureStderr();
  LOG(INFO) << "Test Log Info";
  output = testing::internal::GetCapturedStderr();
  ASSERT_EQ(output.length(), 0);

  testing::internal::CaptureStderr();
  LOG(CONSOLE) << "Test Log Console";
  output = testing::internal::GetCapturedStderr();
  ASSERT_NE(output.find("Test Log Console"), std::string::npos);
}

}  // namespace xgboost
