--- src/cpp/core/include/core/json/Json.hpp.orig	2015-03-06 22:12:51 UTC
+++ src/cpp/core/include/core/json/Json.hpp
@@ -79,6 +79,24 @@ json::Array toJsonArray(const std::vecto
    return results;
 }
 
+template<>
+inline json::Array toJsonArray<bool>(const std::vector<bool>& val)
+{
+   json::Array results;
+
+   std::vector<bool>::const_iterator first = val.begin();
+   std::vector<bool>::const_iterator last  = val.end();
+   std::back_insert_iterator<json::Array> res = std::back_inserter(results);
+
+   while (first != last)
+   {
+     *res = (const bool) *first;
+     ++res; ++first;
+   }
+
+   return results;
+}
+
 bool parse(const std::string& input, Value* pValue);
 
 void write(const Value& value, std::ostream& os);
