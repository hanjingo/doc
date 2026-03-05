import re
from pathlib import Path
from deep_translator import GoogleTranslator

src = Path('feature_zh.md')
dst = Path('feature.md')
lines = src.read_text(encoding='utf-8').splitlines()

translator = GoogleTranslator(source='zh-CN', target='en')
cache = {}

heading_map = {
    'C++特性': 'C++ Features',
    'C++指针': 'C++ Pointers',
    '=default和=delete': '=default and =delete',
    '可变参数': 'variadic arguments',
    '数据类型': 'Data types',
    '参考': 'References',
}

fixed_line_map = {
    '[English](feature.md) | 中文版': 'English | [中文版](feature_zh.md)',
    '[返回顶部](#C++特性)': '[Top](#C++ Features)',
}

link_pat = re.compile(r'\[([^\]]+)\]\(([^)]+)\)')
fence_pat = re.compile(r'^\s*`{3,}')


def has_zh(text: str) -> bool:
    return re.search(r'[\u4e00-\u9fff]', text) is not None


def translate_text(text: str) -> str:
    stripped = text.strip()
    if not stripped:
        return text
    if stripped in cache:
        translated = cache[stripped]
    else:
        try:
            translated = translator.translate(stripped)
        except Exception:
            translated = stripped
        cache[stripped] = translated
    return text.replace(stripped, translated, 1)


in_code = False
out_lines = []

for line in lines:
    if line in fixed_line_map:
        out_lines.append(fixed_line_map[line])
        continue

    if fence_pat.match(line):
        in_code = not in_code
        out_lines.append(line)
        continue

    if line.startswith('#'):
        m = re.match(r'^(#+\s*)(.*)$', line)
        if m:
            prefix, title = m.groups()
            title = heading_map.get(title, title)
            if has_zh(title):
                title = translate_text(title).strip()
            out_lines.append(prefix + title)
            continue

    if in_code:
        if has_zh(line):
            if '//' in line:
                left, right = line.split('//', 1)
                out_lines.append(left + '// ' + translate_text(right).strip())
            elif '/*' in line and '*/' in line:
                start = line.find('/*')
                end = line.rfind('*/')
                inner = line[start + 2:end]
                out_lines.append(line[:start + 2] + ' ' + translate_text(inner).strip() + ' ' + line[end:])
            else:
                out_lines.append(line)
        else:
            out_lines.append(line)
        continue

    if has_zh(line):
        translated_line = line
        matches = list(link_pat.finditer(translated_line))
        if matches:
            rebuilt = ''
            last = 0
            for match in matches:
                rebuilt += translated_line[last:match.start()]
                title, url = match.group(1), match.group(2)
                if has_zh(title):
                    title = translate_text(title).strip()
                rebuilt += f'[{title}]({url})'
                last = match.end()
            rebuilt += translated_line[last:]
            translated_line = rebuilt

        if has_zh(translated_line):
            list_match = re.match(r'^(\s*(?:[-*+]\s+|\d+\.\s+))(.*)$', translated_line)
            if list_match:
                prefix, body = list_match.groups()
                translated_line = prefix + translate_text(body).strip()
            else:
                translated_line = translate_text(translated_line)

        out_lines.append(translated_line)
    else:
        out_lines.append(line)

# keep markdown separators/anchors style aligned to source intent
out_text = '\n'.join(out_lines) + '\n'
out_text = out_text.replace('[返回顶部](#C++特性)', '[Top](#C++ Features)')

dst.write_text(out_text, encoding='utf-8')
print(f'updated {dst} lines={len(out_lines)} cache={len(cache)}')
