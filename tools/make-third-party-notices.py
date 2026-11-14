"""Builds THIRD-PARTY-NOTICES.txt from the licence files vendored in a JUCE checkout.

Usage: python3 tools/make-third-party-notices.py <juce-src> Resources/Fonts/OFL.txt Resources/THIRD-PARTY-NOTICES.txt

The component list and versions follow JUCE 9.0.4's JUCE.spdx.json; check them against that file when JUCE is updated.
"""
import sys, re, pathlib
juce = pathlib.Path(sys.argv[1]); ofl = pathlib.Path(sys.argv[2]); out = pathlib.Path(sys.argv[3])
m = juce / "modules"
def read(p): return (m / p).read_text(encoding="utf-8", errors="replace").strip("\n")
def ijg():
    text = read("juce_graphics/image_formats/jpglib/README")
    start = text.index("LEGAL ISSUES\n============")
    end = text.index("REFERENCES\n==========", start)
    return text[start:end].strip()
chromium = """Copyright 2015 The Chromium Authors

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

   * Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above
copyright notice, this list of conditions and the following disclaimer
in the documentation and/or other materials provided with the
distribution.
   * Neither the name of Google LLC nor the names of its
contributors may be used to endorse or promote products derived from
this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."""
parts = [
 ("VST3 SDK 3.8.0", "MIT", lambda: read("juce_audio_processors_headless/format_types/VST3_SDK/LICENSE.txt")),
 ("AudioUnitSDK 1.1.0", "Apache-2.0", lambda: read("juce_audio_plugin_client/AU/AudioUnitSDK/LICENSE.txt")),
 ("zlib 1.3.2", "Zlib", lambda: read("juce_core/zip/zlib/LICENSE")),
 ("HarfBuzz 14.2.1", "MIT-Modern-Variant", lambda: read("juce_graphics/fonts/harfbuzz/COPYING")),
 ("SheenBidi 2.9.0", "Apache-2.0", lambda: read("juce_graphics/unicode/sheenbidi/LICENSE")),
 ("LunaSVG 3.5.0", "MIT", lambda: read("juce_graphics/drawables/lunasvg/LICENSE")),
 ("PlutoVG 1.3.2", "MIT", lambda: read("juce_graphics/drawables/lunasvg/plutovg/LICENSE")),
 ("libpng 1.6.58", "libpng-2.0", lambda: read("juce_graphics/image_formats/pnglib/LICENSE")),
 ("libjpeg (Independent JPEG Group) 10.0", "IJG", lambda: "This software is based in part on the work of the Independent JPEG Group.\n\n" + ijg()),
 ("libwebp 1.6.0", "BSD-3-Clause", lambda: read("juce_graphics/image_formats/libwebp/COPYING")),
 ("Chromium cubic_bezier", "BSD-3-Clause", lambda: chromium),
 ("FLAC 1.5.0", "BSD-3-Clause", lambda: read("juce_audio_formats/codecs/flac/Flac Licence.txt")),
 ("libogg 1.3.6", "BSD-3-Clause", lambda: read("juce_audio_formats/codecs/ogg/COPYING")),
 ("libvorbis 1.3.7", "BSD-3-Clause", lambda: read("juce_audio_formats/codecs/vorbis/COPYING")),
 ("Opus 1.6.1", "BSD-3-Clause", lambda: read("juce_audio_formats/codecs/opus/opus/COPYING")),
 ("opusfile", "BSD-3-Clause", lambda: read("juce_audio_formats/codecs/opus/opusfile/COPYING")),
 ("libopusenc 0.3", "BSD-3-Clause", lambda: read("juce_audio_formats/codecs/opus/libopusenc/COPYING")),
 ("Barlow fonts", "OFL-1.1", lambda: ofl.read_text(encoding="utf-8").strip("\n")),
]
rule = "=" * 78
lines = ["Third-party notices", "===================", "",
 "This plug-in is built with JUCE 9.0.4 (https://juce.com), used under the GNU",
 "AGPLv3, the same licence as the plug-in itself (see LICENSE). JUCE includes",
 "the third-party code below, some or all of which is compiled into each Lucky",
 "Labs plug-in. The interface is set in the Barlow fonts. Their notices and",
 "licences follow, as published by their authors.", ""]
for name, spdx, get in parts:
    lines += [rule, f"{name} ({spdx})", rule, "", get(), ""]
out.write_text("\n".join(lines) + "\n", encoding="utf-8")
print("wrote", out, len(lines))
