/* Copyright 2012 the SumatraPDF project authors (see AUTHORS file).
   License: GPLv3 */

#ifndef Doc_h
#define Doc_h

// In the past operations on supported document files were done as BaseEngine
// subclass. When we added MobiDoc and MobiWindow, not every document is an engine.
// Class Doc (a short for Document, since it's going to be used frequently)
// is a wrapper/abstractions for them.
// It simply wraps all document objects, allows querying the type, casting
// to the wrapped object and present as much of the unified interface as
// possible.
// It's small enough to be passed as value.
// 
// During transitional period, there wil be a lot of converting to/from
// but the intent is to use Doc and only extract the wrapped object at
// leaf nodes of the code

class BaseEngine;
class CbxEngine;
class ChmEngine;
class Chm2Engine;
class DjVuEngine;
class EpubDoc;
class EpubEngine;
class Fb2Engine;
class ImageEngine;
class ImageDirEngine;
class MobiEngine;
class MobiDoc;
class PdfEngine;
class PsEngine;
class XpsEngine;

class Doc
{
public:
    enum DocType {
        None,
        CbxEng, ChmEng, Chm2Eng, DjVuEng, Epub,
        EpubEng, Fb2Eng, ImageEng, ImageDirEng,
        MobiEng, Mobi, PdfEng, PsEng, XpsEng
    };

    DocType type;
    union {
        void *dummy;
        BaseEngine *engine; // we can always cast to the right type based on type
        EpubDoc * epubDoc;
        MobiDoc * mobiDoc;
    };

    Doc(const Doc& other) { type = other.type; dummy = other.dummy; }
    Doc& operator=(const Doc& other) { type = other.type; dummy = other.dummy; return *this; }

    Doc() { type = None; dummy = NULL; }
    Doc(CbxEngine *doc) { Set(doc); }
    Doc(ChmEngine *doc) { Set(doc); }
    Doc(Chm2Engine *doc) { Set(doc); }
    Doc(DjVuEngine *doc) { Set(doc); }
    Doc(EpubDoc *doc) { Set(doc); }
    Doc(EpubEngine *doc) { Set(doc); }
    Doc(Fb2Engine *doc) { Set(doc); }
    Doc(ImageEngine *doc) { Set(doc); }
    Doc(ImageDirEngine *doc) { Set(doc); }
    Doc(MobiEngine *doc) { Set(doc); }
    Doc(MobiDoc *doc) { Set(doc); }
    Doc(PdfEngine *doc) { Set(doc); }
    Doc(PsEngine *doc) { Set(doc); }
    Doc(XpsEngine *doc) { Set(doc); }

    void Delete();

    // TODO: move to .cpp file where cast to BaseEngine can be verified by the compiler
    void Set(CbxEngine *doc) { type = CbxEng; engine = (BaseEngine*)doc; }
    void Set(ChmEngine *doc) { type = ChmEng; engine = (BaseEngine*)doc; }
    void Set(Chm2Engine *doc) { type = Chm2Eng; engine = (BaseEngine*)doc; }
    void Set(DjVuEngine *doc) { type = DjVuEng; engine = (BaseEngine*)doc; }
    void Set(EpubEngine *doc) { type = EpubEng; engine = (BaseEngine*)doc; }
    void Set(EpubDoc *doc) { type = Epub; epubDoc = doc; }
    void Set(Fb2Engine *doc) { type = Fb2Eng; engine = (BaseEngine*)doc; }
    void Set(ImageEngine *doc) { type = ImageEng; engine = (BaseEngine*)doc; }
    void Set(ImageDirEngine *doc) { type = ImageDirEng; engine = (BaseEngine*)doc; }
    void Set(MobiEngine *doc) { type = MobiEng; engine = (BaseEngine*)doc; }
    void Set(MobiDoc *doc) { type = Mobi; mobiDoc = doc; }
    void Set(PdfEngine *doc) { type = PdfEng; engine = (BaseEngine*)doc; }
    void Set(PsEngine *doc) { type = PsEng; engine = (BaseEngine*)doc; }
    void Set(XpsEngine *doc) { type = XpsEng; engine = (BaseEngine*)doc; }

    // note: find a better name, if possible
    bool IsNone() const { return None == type; }

    bool IsEbook() const;

    BaseEngine *AsEngine() const;
    MobiDoc *AsMobi() const;
    EpubDoc *AsEpub() const;

    TCHAR *GetFilePath() const;
};

#endif