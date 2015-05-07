--- src/cpp/core/system/PosixSched.cpp.orig	2015-03-06 22:12:51 UTC
+++ src/cpp/core/system/PosixSched.cpp
@@ -39,7 +39,7 @@ bool isCpuAffinityEmpty(const CpuAffinit
 
 Error getCpuAffinity(CpuAffinity* pCpus)
 {
-#ifndef __APPLE__
+#if !defined(__APPLE__) && !defined(__FreeBSD__)
    cpu_set_t cs;
    CPU_ZERO(&cs);
    if (::sched_getaffinity(0, sizeof(cs), &cs) == -1)
@@ -64,7 +64,7 @@ Error getCpuAffinity(CpuAffinity* pCpus)
 
 Error setCpuAffinity(const CpuAffinity& cpus)
 {
-#ifndef __APPLE__
+#if !defined(__APPLE__) && !defined(__FreeBSD__)
    cpu_set_t cs;
    CPU_ZERO(&cs);
 
