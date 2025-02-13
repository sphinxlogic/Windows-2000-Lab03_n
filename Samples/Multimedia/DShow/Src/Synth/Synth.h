//==========================================================================;
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//  Copyright (c) 1992 - 1998  Microsoft Corporation.  All Rights Reserved.
//
//--------------------------------------------------------------------------;
//
//  synth.h
//
//  Audio Signal Generator

#ifndef __AUDIOSYNTH__
#define __AUDIOSYNTH__

//CLSID_SynthFilter
//{79A98DE0-BC00-11ce-AC2E-444553540000}
DEFINE_GUID(CLSID_SynthFilter,
0x79a98de0, 0xbc00, 0x11ce, 0xac, 0x2e, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0);

//CLSID_SynthFilterPropertyPage
//{79A98DE1-BC00-11ce-AC2E-444553540000}
DEFINE_GUID(CLSID_SynthPropertyPage,
0x79a98de1, 0xbc00, 0x11ce, 0xac, 0x2e, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0);

const double TWOPI = 6.283185308;
const int MaxFrequency = 20000;
const int MinFrequency = 0;
const int DefaultFrequency = 440;       // A-440
const int MaxAmplitude = 100;
const int MinAmplitude = 0;
const int DefaultSweepStart = DefaultFrequency;
const int DefaultSweepEnd = 5000;
const int WaveBufferSize = 16*1024;     // Size of each allocated buffer
                                        // Originally used to be 2K, but at
                                        // 44khz/16bit/stereo you would get
                                        // audio breaks with a transform in the
                                        // middle.

enum Waveforms {
    WAVE_SINE = 0,
    WAVE_SQUARE,
    WAVE_SAWTOOTH,
    WAVE_SINESWEEP,
    WAVE_LAST           // Always keep this guy last
};

#define WM_PROPERTYPAGE_ENABLE  (WM_USER + 100)

// below stuff is implementation-only....
#ifdef _AUDIOSYNTH_IMPLEMENTATION_

class CSynthStream;

// -------------------------------------------------------------------------
// CAudioSynth
// -------------------------------------------------------------------------

class CAudioSynth {

public:

    CAudioSynth(
                int Frequency = DefaultFrequency,
                int Waveform = WAVE_SINE,
                int iBitsPerSample = 8,
                int iChannels = 1,
                int iSamplesPerSec = 11025,
                int iAmplitude = 100
                );

    ~CAudioSynth();

    // Load the buffer with the current waveform
    void FillAudioBuffer (BYTE pBuf[], int iSize, BOOL * fNewFormat);

    // Set the "current" format and allocate temporary memory
    void AllocWaveCache    (void) ;

    STDMETHODIMP get_Frequency(int *Frequency);
    STDMETHODIMP put_Frequency(int  Frequency);
    STDMETHODIMP get_Waveform(int *Waveform);
    STDMETHODIMP put_Waveform(int  Waveform);
    STDMETHODIMP get_Channels(int *Channels);
    STDMETHODIMP get_BitsPerSample(int *BitsPerSample);
    STDMETHODIMP get_SamplesPerSec(int *SamplesPerSec);
    STDMETHODIMP put_SynthFormat(int Channels, int BitsPerSample, int SamplesPerSec);
    STDMETHODIMP get_Amplitude(int *Amplitude);
    STDMETHODIMP put_Amplitude(int  Amplitude);
    STDMETHODIMP get_SweepRange(int *SweepStart, int *SweepEnd);
    STDMETHODIMP put_SweepRange(int  SweepStart, int  SweepEnd);

private:
    CCritSec m_SynthLock;

    WAVEFORMATEX wfex;          // the current format
    WAVEFORMATEX wfexLast;      // last known waveformat

    int m_iWaveform;            // WAVE_SINE ...
    int m_iFrequency;           // if not using sweep, this is the frequency
    int m_iAmplitude;           // 0 to 100

    int m_iWaveformLast;        // keep track of the last known format
    int m_iFrequencyLast;       // so we can flush the cache if necessary
    int m_iAmplitudeLast;

    int m_iCurrentSample;       // 0 to iSamplesPerSec-1
    BYTE * m_bWaveCache;        // Wave Cache as BYTEs
    WORD * m_wWaveCache;        // Wave Cache as WORDs
    int m_iWaveCacheSize;       // how big is the cache?
    int m_iWaveCacheCycles;     // how many cycles are in the cache
    int m_iWaveCacheIndex;

    int m_iSweepStart;           // start of sweep
    int m_iSweepEnd;             // end of sweep
//    double m_SweepDuration;     // how long the sweep lasts

    void CalcCacheSine     (void) ;
    void CalcCacheSquare   (void) ;
    void CalcCacheSawtooth (void) ;
    void CalcCacheSweep    (void) ;

};



// -------------------------------------------------------------------------
// CSynthFilter
// -------------------------------------------------------------------------
// CSynthFilter manages filter level stuff

class CSynthFilter :    public ISynth,
                        public CPersistStream,
                        public ISpecifyPropertyPages,
                        public CSource {

public:

    static CUnknown * WINAPI CreateInstance(LPUNKNOWN lpunk, HRESULT *phr);
    ~CSynthFilter();

    DECLARE_IUNKNOWN;

    // override this to reveal our property interface
    STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void ** ppv);

    // --- ISpecifyPropertyPages ---

    // return our property pages
    STDMETHODIMP GetPages(CAUUID * pPages);

    // --- IPersistStream Interface

    STDMETHODIMP GetClassID(CLSID *pClsid);
    int SizeMax();
    HRESULT WriteToStream(IStream *pStream);
    HRESULT ReadFromStream(IStream *pStream);

    //
    // --- ISynth ---
    //

    STDMETHODIMP get_Frequency(int *Frequency);
    STDMETHODIMP put_Frequency(int Frequency);
    STDMETHODIMP get_Waveform(int *Waveform);
    STDMETHODIMP put_Waveform(int Waveform);
    STDMETHODIMP get_Channels(int *Channels);
    STDMETHODIMP get_BitsPerSample(int *BitsPerSample);
    STDMETHODIMP get_SamplesPerSec(int *SamplesPerSec);
    STDMETHODIMP put_Channels(int Channels);
    STDMETHODIMP put_BitsPerSample(int BitsPersample);
    STDMETHODIMP put_SamplesPerSec(int SamplesPerSec);
    STDMETHODIMP get_Amplitude(int *Amplitude);
    STDMETHODIMP put_Amplitude(int Amplitude);
    STDMETHODIMP get_SweepRange(int *SweepStart, int *SweepEnd);
    STDMETHODIMP put_SweepRange(int  SweepStart, int  SweepEnd);

    CAudioSynth *m_Synth;           // the current synthesizer
    int		m_Channels;
    int		m_BitsPerSample;
    int		m_SamplesPerSec;

private:

    // it is only allowed to to create these objects with CreateInstance
    CSynthFilter(LPUNKNOWN lpunk, HRESULT *phr);

    // When the format changes, reconnect...
    void CSynthFilter::ReconnectWithNewFormat(void);

};


// -------------------------------------------------------------------------
// CSynthStream
// -------------------------------------------------------------------------
// CSynthStream manages the data flow from the output pin.

class CSynthStream : public CSourceStream {

public:

    CSynthStream(HRESULT *phr, CSynthFilter *pParent, LPCWSTR pPinName);
    ~CSynthStream();

    BOOL ReadyToStop(void) {return FALSE;}

    // stuff an audio buffer with the current format
    HRESULT FillBuffer(IMediaSample *pms);

    // ask for buffers of the size appropriate to the agreed media type.
    HRESULT DecideBufferSize(IMemAllocator *pIMemAlloc,
                             ALLOCATOR_PROPERTIES *pProperties);

    // verify we can handle this format
    HRESULT CheckMediaType(const CMediaType *pMediaType);

    // set the agreed media type
    HRESULT SetMediaType(const CMediaType *pMediaType);

    HRESULT GetMediaType(CMediaType *pmt);

    // resets the stream time to zero.
    HRESULT OnThreadCreate(void);

    HRESULT Active   (void);
    HRESULT Inactive (void);

private:

    // Access to this state information should be serialized with the filters
    // critical section (m_pFilter->pStateLock())

    CCritSec    m_cSharedState;     // use this to lock access to m_rtSampleTime and m_Synth
                                    // which are shared with the worker thread.

    CRefTime     m_rtSampleTime;    // The time to be stamped on each sample
    CAudioSynth *m_Synth;           // the current synthesizer

    CSynthFilter *m_pParent;
};



#endif // _AUDIOSYNTH_IMPLEMENTATION_ implementation only....

#endif /* __AUDIOSYNTH__ */


