--- src/cpp/session/modules/SessionHTMLPreview.cpp.orig	2015-03-06 22:12:51 UTC
+++ src/cpp/session/modules/SessionHTMLPreview.cpp
@@ -529,6 +529,27 @@ Error getHTMLCapabilities(const json::Js
    return Success();
 }
 
+// http://en.cppreference.com/w/cpp/algorithm/search
+template<class ForwardIt1, class ForwardIt2>
+ForwardIt1 search_wa(ForwardIt1 first, ForwardIt1 last,
+                        ForwardIt2 s_first, ForwardIt2 s_last)
+{
+    for (; ; ++first) {
+        ForwardIt1 it = first;
+        for (ForwardIt2 s_it = s_first; ; ++it, ++s_it) {
+            if (s_it == s_last) {
+                return first;
+            }
+            if (it == last) {
+                return last;
+            }
+            if (!(*it == *s_it)) {
+                break;
+            }
+        }
+    }
+}
+
 
 const char* const MAGIC_GUID = "12861c30b10411e1afa60800200c9a66";
 const char* const FIGURE_DIR = "figure-compile-notebook-12861c30b";
@@ -552,7 +573,7 @@ bool okToGenerateFile(const FilePath& rm
 
       std::string magicGuid(MAGIC_GUID);
       std::istreambuf_iterator<char> eod;
-      if (eod == std::search(std::istreambuf_iterator<char>(*pStr),
+      if (eod == /*std::search*/search_wa(std::istreambuf_iterator<char>(*pStr),
                              eod,
                              magicGuid.begin(),
                              magicGuid.end()))
