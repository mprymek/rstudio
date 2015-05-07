--- src/cpp/core/include/core/r_util/RTokenizer.hpp.orig	2015-03-06 22:12:51 UTC
+++ src/cpp/core/include/core/r_util/RTokenizer.hpp
@@ -25,7 +25,7 @@
 #include <boost/regex_fwd.hpp>
 
 // On Linux confirm that wchar_t is Unicode
-#if !defined(_WIN32) && !defined(__APPLE__) && !defined(__STDC_ISO_10646__)
+#if !defined(_WIN32) && !defined(__APPLE__) && !defined(__FreeBSD__) && !defined(__STDC_ISO_10646__)
    #error "wchar_t is not Unicode"
 #endif
 
