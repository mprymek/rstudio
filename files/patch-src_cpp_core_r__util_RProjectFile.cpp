--- src/cpp/core/r_util/RProjectFile.cpp.orig	2015-03-06 22:12:51 UTC
+++ src/cpp/core/r_util/RProjectFile.cpp
@@ -31,6 +31,9 @@
 #include <core/r_util/RPackageInfo.hpp>
 #include <core/r_util/RVersionInfo.hpp>
 
+#undef major
+#undef minor
+
 namespace core {
 namespace r_util {
 
