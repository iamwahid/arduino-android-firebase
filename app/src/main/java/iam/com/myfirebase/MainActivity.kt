package iam.com.myfirebase

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.TextView
import kotlinx.android.synthetic.main.activity_main.*
import com.google.firebase.database.DatabaseReference
import com.google.firebase.database.FirebaseDatabase
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.ValueEventListener
import java.lang.Exception


class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val database: FirebaseDatabase = FirebaseDatabase.getInstance()
        val myLed: DatabaseReference = database.getReference("Led")
        val myDistance: DatabaseReference = database.getReference("Distance")
        var status: String? = ""
        var distance: String? = ""

        val txtJarak = findViewById<TextView>(R.id.txtJarak)

        myLed.addValueEventListener(object : ValueEventListener {
            override fun onDataChange(dataSnapshot: DataSnapshot) {
                // This method is called once with the initial value and again
                // whenever data at this location is updated.
                try {
                    var value = dataSnapshot.getValue(String::class.java)
                    status = value
                    btnLed.text = value
                } catch (e: Exception) {
                    myLed.setValue("OFF")
                }
            }

            override fun onCancelled(error: DatabaseError) {
                // Failed to read value
            }
        })

        myDistance.addValueEventListener(object : ValueEventListener {
            override fun onDataChange(dataSnapshot: DataSnapshot) {
                // This method is called once with the initial value and again
                // whenever data at this location is updated.
                try {
                    var dist = dataSnapshot.getValue(String::class.java)
                    distance = dist
                    txtJarak.text = "Jarak : "+dist+" cm"
                } catch (e: Exception) {
                    myDistance.setValue("0")
                }
            }

            override fun onCancelled(error: DatabaseError) {
                // Failed to read value
            }
        })

        val btnLed = findViewById<Button>(R.id.btnLed)

        btnLed.setOnClickListener {
            if (status == "OFF") {
                myLed.setValue("ON")
                btnLed.text = "ON"
            } else {
                myLed.setValue("OFF")
                btnLed.text = "OFF"
            }
        }
    }
}
