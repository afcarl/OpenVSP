//
// This file is released under the terms of the NASA Open Source Agreement (NOSA)
// version 1.3 as detailed in the LICENSE file which accompanies this software.
//

// VSPAEROMgr.h: interface for the VSPAERO Singleton.
//
//////////////////////////////////////////////////////////////////////

#if !defined(VSPAERO__INCLUDED_)
#define VSPAERO__INCLUDED_

#include "VehicleMgr.h"
#include "Vehicle.h"
#include "Geom.h"
#include "Parm.h"
#include "ProcessUtil.h"

#include <vector>
#include <string>
using std::string;
using std::vector;

//==== VSPAERO Manager ====//
class VSPAEROMgrSingleton : public ParmContainer
{
public:
    static VSPAEROMgrSingleton& getInstance()
    {
        static VSPAEROMgrSingleton instance;
        return instance;
    }
    void Init()                                         {}
    virtual void ParmChanged( Parm* parm_ptr, int type );

    void ClearAllPreviousResults();

    virtual xmlNodePtr EncodeXml( xmlNodePtr & node );
    virtual xmlNodePtr DecodeXml( xmlNodePtr & node );

    void Update();

    void UpdateFilenames();
    std::vector <string> ComputeGeometry();        // returns a vector of results id's
    void CreateSetupFile();
    std::vector <string> ComputeSolver(); // returns a vector of results id's
    ProcessUtil* GetSolverProcess();
    bool IsSolverRunning();
    void KillSolver();
    void ReadAllResults();
    string ReadHistoryFile();
    string ReadLoadFile();
    string ReadStabFile();
    void AddResultHeader(string res_id, double mach, double alpha, double beta);

    // file names
    string m_DegenFile;
    string m_SetupFile;
    string m_AdbFile;
    string m_HistoryFile;
    string m_LoadFile;
    string m_StabFile;

    IntParm m_GeomSet;

    Parm m_Sref;
    Parm m_bref;
    Parm m_cref;
    string m_RefGeomID;
    IntParm m_RefFlag;
    BoolParm m_StabilityCalcFlag;

    IntParm m_CGGeomSet;
    IntParm m_NumMassSlice;
    Parm m_Xcg;
    Parm m_Ycg;
    Parm m_Zcg;

    // Single Point Values (Current Value)
    Parm m_Alpha;
    Parm m_Beta;
    Parm m_Mach;

    // Sweep parameter settings
    Parm m_AlphaStart, m_AlphaEnd; IntParm m_AlphaNpts;
    Parm m_BetaStart, m_BetaEnd; IntParm m_BetaNpts;
    Parm m_MachStart, m_MachEnd; IntParm m_MachNpts;

    // Solver settings
    IntParm m_NCPU;
    IntParm m_WakeNumIter;
    IntParm m_WakeAvgStartIter;
    IntParm m_WakeSkipUntilIter;

    enum { MANUAL_REF = 0, COMPONENT_REF, };

    ProcessUtil m_SolverProcess;

protected: 
    std::string GetFileContents(const char *filename);
    std::string ReplaceAddNameValue(std::string contents, std::string name, std::string value_str);
    
    void WaitForFile(string filename);    // function is used to wait for the result to show up on the file system
private:

    VSPAEROMgrSingleton();
    VSPAEROMgrSingleton( VSPAEROMgrSingleton const& copy );            // Not Implemented
    VSPAEROMgrSingleton& operator=( VSPAEROMgrSingleton const& copy ); // Not Implemented

};

#define VSPAEROMgr VSPAEROMgrSingleton::getInstance()

#endif
