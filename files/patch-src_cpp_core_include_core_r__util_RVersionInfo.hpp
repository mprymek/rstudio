--- src/cpp/core/include/core/r_util/RVersionInfo.hpp.orig	2015-03-06 22:12:51 UTC
+++ src/cpp/core/include/core/r_util/RVersionInfo.hpp
@@ -28,6 +28,9 @@
 #define kRVersionArch32    "32"
 #define kRVersionArch64    "64"
 
+#undef major
+#undef minor
+
 namespace core {
 namespace r_util {
 
