//
//  kern_bt4lefx.hpp
//  BT4LEContinuityFixup
//
//  Copyright © 2017 lvs1974. All rights reserved.
//

#ifndef kern_hooks_hpp
#define kern_hooks_hpp

#include <Headers/kern_patcher.hpp>
#include <stdatomic.h>

class KERNELHOOKS {
public:
	bool init();
	void deinit();
		
		
	static bool areAudioSamplesAvailable();
	
	/**
	 *  Flag is set to true if any audio samples are available
	 */
	static _Atomic(bool) volatile audioSamplesAvailable;
	
	static AbsoluteTime last_audio_event;

private:
	
	/**
	 *  Patch kext if needed and prepare other patches
	 *
	 *  @param patcher KernelPatcher instance
	 *  @param index   kinfo handle
	 *  @param address kinfo load address
	 *  @param size    kinfo memory size
	 */
	void processKext(KernelPatcher &patcher, size_t index, mach_vm_address_t address, size_t size);

	/**
	 *  Hooked methods / callbacks
	 */
	static IOReturn IOAudioStream_processOutputSamples(void *that, void *clientBuffer, UInt32 firstSampleFrame, UInt32 loopCount, bool samplesAvailable);

	/**
	 *  Original method
	 */
	mach_vm_address_t orgIOAudioStream_processOutputSamples {};
};

#endif /* kern_hooks_hpp */
