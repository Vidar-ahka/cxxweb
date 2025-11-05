#include <gtest/gtest.h>
#include "cxxweb/html/htmltemplatekey.h"


namespace CxxWeb
{

    TEST(HTMLTemplateKeyTest, EmptyInput) {
         ByteArray byte;
        HTMLTemplateKey tpl(byte);
        ByteArray html;
        tpl.setDataHtml(html);
        
        std::unordered_map<std::string, std::string> vars;
        ByteArray result = tpl.get(vars);
        EXPECT_TRUE(result.empty());
    }
    
    TEST(HTMLTemplateKeyTest, SimpleKeyReplacement) {
        ByteArray html;
        html.write("Hello, {{name}}!");
        HTMLTemplateKey tpl(html);
        
        tpl.setDataHtml(html);
        std::unordered_map<std::string, std::string> vars = {{"name", "Alice"}};
        ByteArray result = tpl.get(vars);
        
        EXPECT_EQ(std::string(result.data(), result.size()), "Hello, Alice!");
    }
    
    TEST(HTMLTemplateKeyTest, MultipleKeysReplacement) {
        ByteArray html;
        html.write("{{greet}}, {{name}}! Welcome to {{place}}.");
        HTMLTemplateKey tpl(html);
        
        tpl.setDataHtml(html);
        std::unordered_map<std::string, std::string> vars = {
            {"greet", "Hi"},
            {"name", "Bob"},
            {"place", "Wonderland"}
        };
        
        ByteArray result = tpl.get(vars);
        EXPECT_EQ(std::string(result.data(), result.size()), "Hi, Bob! Welcome to Wonderland.");
    }

    TEST(HTMLTemplateKeyTest, InvalidKeyIgnored) {
        ByteArray html;
        html.write("{{a b}} and {{ok}}");
        HTMLTemplateKey tpl(html);
        
        tpl.setDataHtml(html);
        std::unordered_map<std::string, std::string> vars = {{"ok", "fine"}};
        ByteArray result = tpl.get(vars);
        
        // "{{a b}}" игнорируется, только "{{ok}}" заменяется
        EXPECT_EQ(std::string(result.data(), result.size()), "{{a b}} and fine");
    }
    
    TEST(HTMLTemplateKeyTest, TextWithoutKeys) {
        ByteArray html;
        html.write("No placeholders here.");
        HTMLTemplateKey tpl(html);
        
        tpl.setDataHtml(html);
        std::unordered_map<std::string, std::string> vars;
        ByteArray result = tpl.get(vars);
        
        EXPECT_EQ(std::string(result.data(), result.size()), "No placeholders here.");
}

TEST(HTMLTemplateKeyTest, HandlesSpacesInText) {
    ByteArray html;
    html.write("{{key}}  text  {{another}}");
    HTMLTemplateKey tpl(html);
    
    tpl.setDataHtml(html);
    std::unordered_map<std::string, std::string> vars = {
        {"key", "A"},
        {"another", "B"}
    };
    
    ByteArray result = tpl.get(vars);
    EXPECT_EQ(std::string(result.data(), result.size()), "A  text  B");
}

}