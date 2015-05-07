--- src/cpp/core/system/PosixSystem.cpp.orig	2015-03-06 22:12:51 UTC
+++ src/cpp/core/system/PosixSystem.cpp
@@ -43,13 +43,18 @@
 #include <mach-o/dyld.h>
 #endif
 
-#ifndef __APPLE__
+#if !defined(__APPLE__) && !defined(__FreeBSD__)
 #include <sys/prctl.h>
 #include <sys/sysinfo.h>
 #include <linux/kernel.h>
 #include <dirent.h>
 #endif
 
+#ifdef __FreeBSD__
+#include <netinet/in.h>
+#include <sys/sysctl.h>
+#endif
+
 #include <boost/thread.hpp>
 #include <boost/format.hpp>
 #include <boost/lexical_cast.hpp>
@@ -662,9 +667,20 @@ Error executablePath(const char * argv0,
    //
 
    // use argv[0] and initial path
+   /* initialPath() not present in FilePath anymore
    FilePath initialPath = FilePath::initialPath();
    executablePath = initialPath.complete(argv0).absolutePath();
+   */
+   int mib[4];
+   mib[0] = CTL_KERN;
+   mib[1] = KERN_PROC;
+   mib[2] = KERN_PROC_PATHNAME;
+   mib[3] = -1;
+   char buffer[2048];
+   size_t cb = sizeof(buffer);
+   sysctl(mib, 4, buffer, &cb, NULL, 0);
 
+   executablePath = std::string(&(buffer[0]));
 #endif
 
    // return realPath of executable path
@@ -777,7 +793,7 @@ Error osResourceLimit(ResourceLimit limi
       case CpuLimit:
          *pLimit = RLIMIT_CPU;
          break;
-#ifndef __APPLE__
+#if !defined(__APPLE__) && !defined(__FreeBSD__)
       case NiceLimit:
          *pLimit = RLIMIT_NICE;
          break;
@@ -850,7 +866,7 @@ Error systemInformation(SysInfo* pSysInf
 {
    pSysInfo->cores = boost::thread::hardware_concurrency();
 
-#ifndef __APPLE__
+#if !defined(__APPLE__) && !defined(__FreeBSD__)
    struct sysinfo info;
    if (::sysinfo(&info) == -1)
       return systemError(errno, ERROR_LOCATION);
@@ -883,7 +899,7 @@ void toPids(const std::vector<std::strin
 
 } // anonymous namespace
 
-#ifndef __APPLE__
+#if !defined(__APPLE__) && !defined(__FreeBSD__)
 core::Error pidof(const std::string& process, std::vector<PidType>* pPids)
 {
    // use pidof to capture pids
@@ -1085,7 +1101,7 @@ Error restrictCoreDumps()
       return error;
 
    // no ptrace core dumps permitted
-#ifndef __APPLE__
+#if !defined(__APPLE__) && !defined(__FreeBSD__)
    int res = ::prctl(PR_SET_DUMPABLE, 0);
    if (res == -1)
       return systemError(errno, ERROR_LOCATION);
@@ -1111,7 +1127,7 @@ void printCoreDumpable(const std::string
    ostr << "  hard limit: " << rLimitHard << std::endl;
 
    // ptrace
-#ifndef __APPLE__
+#if !defined(__APPLE__) && !defined(__FreeBSD__)
    int dumpable = ::prctl(PR_GET_DUMPABLE, NULL, NULL, NULL, NULL);
    if (dumpable == -1)
       LOG_ERROR(systemError(errno, ERROR_LOCATION));
@@ -1183,7 +1199,7 @@ void setProcessLimits(ProcessLimits limi
    }
 
    // cpu affinity
-#ifndef __APPLE__
+#if !defined(__APPLE__) && !defined(__FreeBSD__)
    if (!isCpuAffinityEmpty(limits.cpuAffinity))
    {
       Error error = setCpuAffinity(limits.cpuAffinity);
