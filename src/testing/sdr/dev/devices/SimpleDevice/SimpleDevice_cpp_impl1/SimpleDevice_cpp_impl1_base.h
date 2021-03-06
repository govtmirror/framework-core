/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file 
 * distributed with this source distribution.
 * 
 * This file is part of REDHAWK core.
 * 
 * REDHAWK core is free software: you can redistribute it and/or modify it 
 * under the terms of the GNU Lesser General Public License as published by the 
 * Free Software Foundation, either version 3 of the License, or (at your 
 * option) any later version.
 * 
 * REDHAWK core is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License 
 * for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License 
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

#ifndef SIMPLEDEVICE_CPP_IMPL1_IMPL_BASE_H
#define SIMPLEDEVICE_CPP_IMPL1_IMPL_BASE_H

#include <boost/thread.hpp>
#include <ossie/Resource_impl.h>

#include "ossie/ExecutableDevice_impl.h"

#define NOOP 0
#define FINISH -1
#define NORMAL 1

class SimpleDevice_cpp_impl1_base;


template < typename TargetClass >
class ProcessThread
{
    public:
        ProcessThread(TargetClass *_target, float _delay) :
            target(_target)
        {
            _mythread = 0;
            _thread_running = false;
            _udelay = (__useconds_t)(_delay * 1000000);
        };

        // kick off the thread
        void start() {
            if (_mythread == 0) {
                _thread_running = true;
                _mythread = new boost::thread(&ProcessThread::run, this);
            }
        };

        // manage calls to target's service function
        void run() {
            int state = NORMAL;
            while (_thread_running and (state != FINISH)) {
                state = target->serviceFunction();
                if (state == NOOP) usleep(_udelay);
            }
        };

        // stop thread and wait for termination
        bool release(unsigned long secs = 0, unsigned long usecs = 0) {
            _thread_running = false;
            if (_mythread)  {
                if ((secs == 0) and (usecs == 0)){
                    _mythread->join();
                } else {
                    boost::system_time waitime= boost::get_system_time() + boost::posix_time::seconds(secs) +  boost::posix_time::microseconds(usecs) ;
                    if (!_mythread->timed_join(waitime)) {
                        return 0;
                    }
                }
                delete _mythread;
                _mythread = 0;
            }
    
            return 1;
        };

        virtual ~ProcessThread(){
            if (_mythread != 0) {
                release(0);
                _mythread = 0;
            }
        };

        void updateDelay(float _delay) { _udelay = (__useconds_t)(_delay * 1000000); };

    private:
        boost::thread *_mythread;
        bool _thread_running;
        TargetClass *target;
        __useconds_t _udelay;
        boost::condition_variable _end_of_run;
        boost::mutex _eor_mutex;
};

class SimpleDevice_cpp_impl1_base : public ExecutableDevice_impl
{

    public:
        SimpleDevice_cpp_impl1_base(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl);
        SimpleDevice_cpp_impl1_base(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, char *compDev);
        SimpleDevice_cpp_impl1_base(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities);
        SimpleDevice_cpp_impl1_base(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities, char *compDev);

        void start() throw (CF::Resource::StartError, CORBA::SystemException);

        void stop() throw (CF::Resource::StopError, CORBA::SystemException);

        void releaseObject() throw (CF::LifeCycle::ReleaseError, CORBA::SystemException);

        void initialize() throw (CF::LifeCycle::InitializeError, CORBA::SystemException);

        void configure(const CF::Properties&) throw (CORBA::SystemException, CF::PropertySet::InvalidConfiguration, CF::PropertySet::PartialConfiguration);

        void loadProperties();

        virtual int serviceFunction() = 0;

    protected:
        ProcessThread<SimpleDevice_cpp_impl1_base> *serviceThread; 
        boost::mutex serviceThreadLock;  

        // Member variables exposed as properties
        std::string os_name;
        std::string os_version;
        CORBA::Long memTotal;
        CORBA::Long memFree;
        CORBA::Long memCapacity;
        CORBA::Long memThreshold;
        std::string processor_name;
        CORBA::Long bogomipsPerCPU;
        CORBA::Long bogomipsTotal;
        CORBA::Long bogomipsCapacity;
        CORBA::Long bogomipsThreshold;
        CORBA::Long mcastnicTotal;
        std::string mcastnicInterface;
        CORBA::Long mcastnicCapacity;
        CORBA::Long mcastnicHasVLAN;
        CORBA::Long mcastnicThreshold;
        CORBA::Long diskTotal;
        CORBA::Long diskFree;
        CORBA::Long diskCapacity;
        CORBA::Long diskThreshold;
        CORBA::Long diskrateCapacity;
        std::string diskHasMountPoint;
        std::string hostName;
        std::string DeviceKind;
    
    private:
        void construct();

};
#endif
