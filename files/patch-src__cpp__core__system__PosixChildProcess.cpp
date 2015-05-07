--- src/cpp/core/system/PosixChildProcess.cpp.orig	2015-03-06 22:12:51 UTC
+++ src/cpp/core/system/PosixChildProcess.cpp
@@ -23,6 +23,11 @@
 #include <util.h>
 #include <sys/ttycom.h>
 #include <sys/ioctl.h>
+#elif defined __FreeBSD__
+#include <libutil.h>
+#include <sys/ttycom.h>
+#include <sys/ioctl.h>
+#include <termios.h>
 #else
 #include <pty.h>
 #include <asm/ioctls.h>
