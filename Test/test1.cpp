#include <algorithm>
#include <iostream>
#include <string>
#include <type_traits>
#include <variant>
#include <string>
#include <vector>
#include <yoga/Yoga.h>
#include <sstream>

float longestWordWidth(std::string_view text, float widthPerChar)
{
    int maxLength     = 0;
    int currentLength = 0;
    for (auto c : text)
    {
        if (c == ' ')
        {
            maxLength     = std::max(currentLength, maxLength);
            currentLength = 0;
        }
        else
        {
            currentLength++;
        }
    }
    return (float) std::max(currentLength, maxLength) * widthPerChar;
}

float calculateHeight(std::string_view text, float measuredWidth, float widthPerChar, float heightPerChar)
{
    if ((float) text.size() * widthPerChar <= measuredWidth)
    {
        return heightPerChar;
    }

    std::vector<std::string> words;
    std::istringstream iss((std::string) text);
    std::string currentWord;
    while (getline(iss, currentWord, ' '))
    {
        words.push_back(currentWord);
    }

    float lines             = 1;
    float currentLineLength = 0;
    for (const std::string& word : words)
    {
        float wordWidth = (float) word.length() * widthPerChar;
        if (wordWidth > measuredWidth)
        {
            if (currentLineLength > 0)
            {
                lines++;
            }
            lines++;
            currentLineLength = 0;
        }
        else if (currentLineLength + wordWidth <= measuredWidth)
        {
            currentLineLength += wordWidth + widthPerChar;
        }
        else
        {
            lines++;
            currentLineLength = wordWidth + widthPerChar;
        }
    }
    return (currentLineLength == 0 ? lines - 1 : lines) * heightPerChar;
}

YGSize
IntrinsicSizeMeasure(YGNodeConstRef node, float width, YGMeasureMode widthMode, float height, YGMeasureMode heightMode)
{
    std::string_view innerText((char*) YGNodeGetContext(node));
    float heightPerChar = 10;
    float widthPerChar  = 10;
    float measuredWidth;
    float measuredHeight;

    if (widthMode == YGMeasureModeExactly)
    {
        measuredWidth = width;
    }
    else if (widthMode == YGMeasureModeAtMost)
    {
        measuredWidth = std::min((float) innerText.size() * widthPerChar, width);
    }
    else
    {
        measuredWidth = (float) innerText.size() * widthPerChar;
    }

    if (heightMode == YGMeasureModeExactly)
    {
        measuredHeight = height;
    }
    else if (heightMode == YGMeasureModeAtMost)
    {
        measuredHeight = std::min(
          calculateHeight(
            innerText,
            YGNodeStyleGetFlexDirection(node) == YGFlexDirectionColumn
              ? measuredWidth
              : std::max(longestWordWidth(innerText, widthPerChar), measuredWidth),
            widthPerChar,
            heightPerChar),
          height);
    }
    else
    {
        measuredHeight = calculateHeight(
          innerText,
          YGNodeStyleGetFlexDirection(node) == YGFlexDirectionColumn
            ? measuredWidth
            : std::max(longestWordWidth(innerText, widthPerChar), measuredWidth),
          widthPerChar,
          heightPerChar);
    }
    std::cout << "measuredWidth: " << measuredWidth << std::endl;
    return YGSize{measuredWidth, measuredHeight};
}

int main()
{
    YGConfigRef config = YGConfigNew();

    YGNodeRef root     = YGNodeNewWithConfig(config);
    YGNodeStyleSetPositionType(root, YGPositionTypeAbsolute);
    YGNodeStyleSetWidth(root, 200);

    YGNodeRef root_child0 = YGNodeNewWithConfig(config);
    YGNodeInsertChild(root, root_child0, 0);

    YGNodeRef root_child0_child0 = YGNodeNewWithConfig(config);
    YGNodeStyleSetFlexDirection(root_child0_child0, YGFlexDirectionRow);
    YGNodeInsertChild(root_child0, root_child0_child0, 0);
    YGNodeSetContext(root_child0_child0,
                     (void*) "Lorem ipsum "
                             "AAA "
                             "sdafhasdfkjlasdhlkajsfhasldkfhasdlkahsdflkjasdhflaksdfasdlkjhasdlfjahsdfljkasdhalsdfhas "
                             "dolor sit amet");
    YGNodeSetMeasureFunc(root_child0_child0, &IntrinsicSizeMeasure);
    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

    //ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
    //ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
    //ASSERT_FLOAT_EQ(200, YGNodeLayoutGetWidth(root));
    //ASSERT_FLOAT_EQ(30, YGNodeLayoutGetHeight(root));
    auto v1 = YGNodeLayoutGetLeft(root);
    auto v2 = YGNodeLayoutGetTop(root);
    auto v3 = YGNodeLayoutGetWidth(root);
    auto v4 = YGNodeLayoutGetHeight(root);


    //ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
    //ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
    //ASSERT_FLOAT_EQ(870, YGNodeLayoutGetWidth(root_child0));
    //ASSERT_FLOAT_EQ(30, YGNodeLayoutGetHeight(root_child0));
    auto v5 = YGNodeLayoutGetLeft(root_child0);
    auto v6 = YGNodeLayoutGetTop(root_child0);
    auto v7 = YGNodeLayoutGetWidth(root_child0);
    auto v8 = YGNodeLayoutGetHeight(root_child0);

    //ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0_child0));
    //ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0_child0));
    //ASSERT_FLOAT_EQ(870, YGNodeLayoutGetWidth(root_child0_child0));
    //ASSERT_FLOAT_EQ(30, YGNodeLayoutGetHeight(root_child0_child0));

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

    //ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
    //ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
    //ASSERT_FLOAT_EQ(200, YGNodeLayoutGetWidth(root));
    //ASSERT_FLOAT_EQ(30, YGNodeLayoutGetHeight(root));

    //ASSERT_FLOAT_EQ(-670, YGNodeLayoutGetLeft(root_child0));
    //ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
    //ASSERT_FLOAT_EQ(870, YGNodeLayoutGetWidth(root_child0));
    //ASSERT_FLOAT_EQ(30, YGNodeLayoutGetHeight(root_child0));

    //ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0_child0));
    //ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0_child0));
    //ASSERT_FLOAT_EQ(870, YGNodeLayoutGetWidth(root_child0_child0));
    //ASSERT_FLOAT_EQ(30, YGNodeLayoutGetHeight(root_child0_child0));

    YGNodeFreeRecursive(root);

    YGConfigFree(config);
    return 0;
}
