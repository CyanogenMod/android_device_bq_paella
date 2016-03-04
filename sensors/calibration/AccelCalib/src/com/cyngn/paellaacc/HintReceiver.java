package com.cyngn.paellaacc;

import static com.android.internal.telephony.TelephonyIntents.SECRET_CODE_ACTION;

import android.content.Context;
import android.content.Intent;
import android.content.BroadcastReceiver;
import android.hardware.Sensor;
import android.hardware.SensorManager;
import android.os.SystemProperties;
import android.util.Log;
import android.view.KeyEvent;
import android.widget.Toast;

import com.cyngn.paellaacc.R;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.ObjectOutputStream;

public class HintReceiver extends BroadcastReceiver {

    private static final String SECRET_CODE_PREFIX = "android_secret_code://";
    public HintReceiver() {
    }

    private String readAccValues(FileReader reader) {
        if (reader != null) {
            try{
                BufferedReader dr = new BufferedReader(reader);
                String val = dr.readLine();
                dr.close();
                return val;
            } catch(IOException e) {
            }
        }
        return null;
   }

    @Override
    public void onReceive(Context context, Intent intent) {
        String accx_wpath;
        String accy_wpath;
        String accz_wpath;

        String accx_rpath;
        String accy_rpath;
        String accz_rpath;

        FileReader xReader = null;
        FileWriter xWriter = null;
        FileReader yReader = null;
        FileWriter yWriter = null;
        FileReader zReader = null;
        FileWriter zWriter = null;

        String sensor_path = "/persist/g_sensor_correct";

        String basePath = "";

        String path = "/sys/class/input";
        File baseDir = new File(path);
        String nodePath;

        File[] files = baseDir.listFiles();

        for (int i=0; i<files.length; i++) {
                if (files[i].getName().startsWith("event")) {
                        nodePath = files[i].getAbsolutePath()+"/device/acc_fast_calibration_x";
                        File tempFile = new File(nodePath);
                        if (tempFile.exists()) {
                                basePath = files[i].getAbsolutePath()+"/device/";
                        }
                }
        }

        if (basePath == "") return;

        accx_wpath = basePath + "acc_fast_calibration_x";
        accy_wpath = basePath + "acc_fast_calibration_y";
        accz_wpath = basePath + "acc_fast_calibration_z";
        accx_rpath = basePath + "acc_offset_x";
        accy_rpath = basePath + "acc_offset_y";
        accz_rpath = basePath + "acc_offset_z";

        try{
                xReader = new FileReader(accx_rpath);
                yReader = new FileReader(accy_rpath);
                zReader = new FileReader(accz_rpath);

                xWriter = new FileWriter(accx_wpath);
                yWriter = new FileWriter(accy_wpath);
                zWriter = new FileWriter(accz_wpath);
        } catch(Exception e) {
                return;
        }


        if (xWriter == null || yWriter == null || zWriter == null)
                return;

        try{
                xWriter.write("3");
                xWriter.flush();
                yWriter.write("3");
                yWriter.flush();
                zWriter.write("1");
                zWriter.flush();
        } catch (IOException e) {
                return;
        }

        String[] accValues = new String[3];

        try{
                accValues[0] = readAccValues(xReader);
                accValues[1] = readAccValues(yReader);
                accValues[2] = readAccValues(zReader);
                ObjectOutputStream sensorWriter = new ObjectOutputStream(new FileOutputStream(sensor_path));
                sensorWriter.writeObject(accValues);
                sensorWriter.close();
        } catch (IOException e) {
                return;
        }

        Toast.makeText(context, R.string.acc_calibration_complete, Toast.LENGTH_LONG).show();
    }
}
